#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include<signal.h>
#include<unistd.h>

static volatile int event_fd;
int set_interface_attribs(int fd, int speed)
{
    struct termios tty;
    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

const char portname[] = "/dev/ttyUSB2";
struct sigaction act;

void signal_handler_IO (int sig, siginfo_t *si, void *data1)
{
  #ifdef DEBUG
  event_fd = si->si_pid;
  printf("Event PID: %d\n",si->si_pid);
  #endif
}

int main(int argc, char** argv)
{
  int fd;
  /* install the signal handler before making the device asynchronous */
  act.sa_sigaction = signal_handler_IO;
  act.sa_flags = 0;
  act.sa_restorer = NULL;
  sigaction(SIGIO,&act,NULL);

  fd = open(portname, O_RDWR | O_NOCTTY | O_NONBLOCK | O_SYNC );
  if (fd < 0) {
      printf("Error opening %s: %s\n", portname, strerror(errno));
      return -1;
  }

  /*baudrate 9600, 8 bits, no parity, 1 stop bit */
  set_interface_attribs(fd, B9600);
  pid_t fork_pid = fork();
  if (fork_pid == 0) {
    unsigned char data;
    fd_set rfds;
    struct timeval tv;
    int retval;
    while(1){
      /* Watch stdin (fd 0) to see when it has input. */
      FD_ZERO(&rfds);
      FD_SET(0, &rfds);
      /* Wait up to five seconds. */
      tv.tv_sec = 5;
      retval = select(1, &rfds, NULL, NULL, &tv);

      if (retval == -1){
        perror("select()");
      }
      else if (retval){
        read(STDIN_FILENO,&data,1);
        write(fd,&data,1);
      }
      #ifdef DEBUG
      else{printf("\n...\n");}
      #endif
    }
  }
  else {
    unsigned char data;
    fcntl(fd, F_SETOWN, getpid());
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_ASYNC);

    while(1){
      pause();
      if(read(fd,&data,1)>0){
        write(STDOUT_FILENO,&data,1);
      }
    }
  }

  close(fd);
}

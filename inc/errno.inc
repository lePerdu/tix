;
; errno.inc
;
; Defines error values.
;

#ifndef ERRNO_INC_
#define ERRNO_INC_

;; Argument list too long.
E2BIG .equ 1

;; Permission denied.
EACCES .equ 2

;; Address in use.
EADDRINUSE .equ 3

;; Address not available.
EADDRNOTAVAIL .equ 4

;; Address family not supported.
EAFNOSUPPORT .equ 5

;; Resource unavailable, try again.
EAGAIN .equ 6

;; Operation would block.
EWOULDBLOCK .equ EAGIN

;; Connection already in progress.
EALREADY .equ 7

;; Bad file descriptor.
EBADF .equ 8

;; Bad message.
EBADMSG .equ 9

;; Device or resource busy.
EBUSY .equ 10

;; Operation canceled.
ECANCELED .equ 11

;; No child processes.
ECHILD .equ 12

;; Connection aborted.
ECONNABORTED .equ 13

;; Connection refused.
ECONNREFUSED .equ 14

;; Connection reset.
ECONNRESET .equ 15

;; Resource deadlock would occur.
EDEADLK .equ 16

;; Destination address required.
EDESTADDRREQ .equ 17

;; Mathematics argument out of domain of function.
EDOM .equ 18

;; Reserved.
EDQUOT .equ 19

;; File exists.
EEXIST .equ 20

;; Bad address.
EFAULT .equ 21

;; File too large.
EFBIG .equ 22

;; Host is unreachable.
EHOSTUNREACH .equ 23

;; Identifier removed.
EIDRM .equ 24

;; Illegal byte sequence.
EILSEQ .equ 25

;; Operation in progress.
EINPROGRESS .equ 26

;; Interrupted function.
EINTR .equ 27

;; Invalid argument.
EINVAL .equ 28

;; I/O error.
EIO .equ 29

;; Socket is connected.
EISCONN .equ 30

;; Is a directory.
EISDIR .equ 31

;; Too many levels of symbolic links.
ELOOP .equ 32

;; File descriptor value too large.
EMFILE .equ 33

;; Too many links.
EMLINK .equ 34

;; Message too large.
EMSGSIZE .equ 35

;; Reserved.
EMULTIHOP .equ 36

;; Filename too long.
ENAMETOOLONG .equ 37

;; Network is down.
ENETDOWN .equ 38

;; Connection aborted by network.
ENETRESET .equ 39

;; Network unreachable.
ENETUNREACH .equ 40

;; Too many files open in system.
ENFILE .equ 41

;; No buffer space available.
ENOBUFS .equ 42

;; [OB XSR] [Option Start] No message is available on the STREAM head read queue. [Option End]
ENODATA .equ 43

;; No such device.
ENODEV .equ 44

;; No such file or directory.
ENOENT .equ 45

;; Executable file format error.
ENOEXEC .equ 46

;; No locks available.
ENOLCK .equ 47

;; Reserved.
ENOLINK .equ 48

;; Not enough space.
ENOMEM .equ 49

;; No message of the desired type.
ENOMSG .equ 50

;; Protocol not available.
ENOPROTOOPT .equ 51

;; No space left on device.
ENOSPC .equ 52

;; [OB XSR] [Option Start] No STREAM resources. [Option End]
ENOSR .equ 53

;; [OB XSR] [Option Start] Not a STREAM. [Option End]
ENOSTR .equ 54

;; Functionality not supported.
ENOSYS .equ 55

;; The socket is not connected.
ENOTCONN .equ 56

;; Not a directory or a symbolic link to a directory.
ENOTDIR .equ 57

;; Directory not empty.
ENOTEMPTY .equ 58

;; State not recoverable.
ENOTRECOVERABLE .equ 59

;; Not a socket.
ENOTSOCK .equ 60

;; Not supported.
ENOTSUP .equ 61

;; Operation not supported on socket.
EOPNOTSUPP .equ ENOTSUP

;; Inappropriate I/O control operation.
ENOTTY .equ 62

;; No such device or address.
ENXIO .equ 63

;; Value too large to be stored in data type.
EOVERFLOW .equ 64

;; Previous owner died.
EOWNERDEAD .equ 65

;; Operation not permitted.
EPERM .equ 66

;; Broken pipe.
EPIPE .equ 67

;; Protocol error.
EPROTO .equ 68

;; Protocol not supported.
EPROTONOSUPPORT .equ 69

;; Protocol wrong type for socket.
EPROTOTYPE .equ 70

;; Result too large.
ERANGE .equ 71

;; Read-only file system.
EROFS .equ 72

;; Invalid seek.
ESPIPE .equ 73

;; No such process.
ESRCH .equ 74

;; Reserved.
ESTALE .equ 75

;; [OB XSR] [Option Start] Stream ioctl() timeout. [Option End]
ETIME .equ 76

;; Connection timed out.
ETIMEDOUT .equ 77

;; Text file busy.
ETXTBSY .equ 78

;; Cross-device link.
EXDEV .equ 79

;; Custom one made by me for non-implemented features
ENOIMPL .equ $FF

#endif


# ft_printf
ft_printf with all the bonus without malloc and without libft using 4 .c files only
here the moulinette log:
= Host-specific information ====================================================
$> hostname; uname -msr
z3t8c2.42bangkok.com
Darwin 19.6.0 x86_64
$> date
Thu Sep  7 12:17:08 +07 2023

= User files collection ========================================================
Collecting user files from Vogsphere
Repository URL: git@vogsphere.42bangkok.com:vogsphere/intra-uuid-1be11966-664b-48e1-b81e-babe091d770b-5099916-tlemoine

= Git history ==================================================================
$> git -C /tmp/tmpkxiaxnnz/user log --pretty='%H - %an, %ad : %s'
aa1e6c9ac89fe6578052f8abc6734436cb5b5a3f - tlemoine, Thu Sep 7 05:42:47 2023 +0700 : -a
32820ab69b5d29a0778e851d9046faf31ea2ce40 - tlemoine, Thu Sep 7 05:42:01 2023 +0700 : -a
 
= Collected files ==========================================
$> ls -lAR /tmp/tmpkxiaxnnz/user
total 16
-rwxr-xr-x  1 root  wheel  1472 Sep  7 12:17 Makefile
-rw-r--r--  1 root  wheel   947 Sep  7 12:17 __GIT_HISTORY
drwxr-xr-x  3 root  wheel    96 Sep  7 12:17 includes
drwxr-xr-x  6 root  wheel   192 Sep  7 12:17 srcs

/tmp/tmpkxiaxnnz/user/includes:
total 8
-rw-r--r--  1 root  wheel  3224 Sep  7 12:17 ft_printf.h

/tmp/tmpkxiaxnnz/user/srcs:
total 40
-rw-r--r--  1 root  wheel  2340 Sep  7 12:17 ft_printf.c
-rw-r--r--  1 root  wheel  3535 Sep  7 12:17 inititalizers.c
-rw-r--r--  1 root  wheel  4418 Sep  7 12:17 printers.c
-rw-r--r--  1 root  wheel  3145 Sep  7 12:17 updaters.c
 
= test_spdxiucpercent ==========================================================
$> /usr/bin/norminette  inititalizers.c includes/ft_printf.h srcs/printers.c ft_printf.c srcs/inititalizers.c printers.c updaters.c srcs/ft_printf.c srcs/updaters.c ft_printf.h | grep -E '^(Error|Warning)'

/bin/rm -f -r ./build
Compiling srcs/ft_printf.c
Compiling srcs/updaters.c
Compiling srcs/inititalizers.c
Compiling srcs/printers.c
Linking libftprintf.a
Done!
/bin/rm -f -r ./build
/bin/rm -f libftprintf.a
Compiling srcs/ft_printf.c
Compiling srcs/updaters.c
Compiling srcs/inititalizers.c
Compiling srcs/printers.c
Linking libftprintf.a
Done!
/bin/rm -f -r ./build
/bin/rm -f libftprintf.a
Compiling srcs/ft_printf.c
Compiling srcs/updaters.c
Compiling srcs/inititalizers.c
Compiling srcs/printers.c
Linking libftprintf.a
Done!
-rw-r--r--  1 deepthought  staff  13448 Sep  7 05:17 libftprintf.a

clang -Wall -Wextra -Werror -fsanitize=address   -c -o test_s.o test_s.c
clang -Wall -Wextra -Werror -fsanitize=address   -c -o test_d.o test_d.c
clang -Wall -Wextra -Werror -fsanitize=address   -c -o test_p.o test_p.c
clang -Wall -Wextra -Werror -fsanitize=address   -c -o test_x.o test_x.c
clang -Wall -Wextra -Werror -fsanitize=address   -c -o test_i.o test_i.c
clang -Wall -Wextra -Werror -fsanitize=address   -c -o test_u.o test_u.c
clang -Wall -Wextra -Werror -fsanitize=address   -c -o test_c.o test_c.c
clang -Wall -Wextra -Werror -fsanitize=address   -c -o test_mix.o test_mix.c
clang -Wall -Wextra -Werror -fsanitize=address   -c -o main.o main.c
clang -Wall -Wextra -Werror -fsanitize=address -o test_printf -L. test_s.o test_d.o test_p.o test_x.o test_i.o test_u.o test_c.o test_mix.o main.o -lftprintf

Command './test_printf' got killed by signal -4
Grade: 0

= Final grade: 25 ==============================================================

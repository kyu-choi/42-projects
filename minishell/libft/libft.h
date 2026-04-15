/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:05:14 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/16 13:20:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

/* ----------------- Part 1 - Libc Functions ----------------- */
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);

/* ----------------- Part 2 - Additional Functions ----------------- */
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/* ----------------- Bonus Part - List Functions ----------------- */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new_node);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new_node);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

/*
** =============================================================================
**                             ADDED FROM FT_PRINTF
** =============================================================================
*/

// Struct to store parsed flags, width, and precision information.
// ├ minus: '-' flag (0: right-align, 1: left-align)
// ├ zero: '0' flag (0: pad with space, 1: pad with zero)
// ├ width: Minimum width value
// ├ precision: '.' precision value (-1: not specified)
// ├ hash: '#' flag (1: use 0x/0X prefix)
// ├ space: ' ' flag (1: prepend space for positive numbers)
// ├ plus: '+' flag (1: prepend '+' for positive numbers)
// └ specifier: The final format specifier (c, s, p, d, i, u, x, X, %)
typedef struct s_flags
{
	int		minus;
	int		zero;
	int		width;
	int		precision;
	int		hash;
	int		space;
	int		plus;
	char	specifier;
}	t_flags;

/*
 * ============================================================================
 * Function Prototypes
 * ============================================================================
*/

// ft_printf_main.c: The main entry point function
int				ft_printf(const char *format, ...);

// ft_printf_parse_flags.c: Functions related to flag parsing
void			init_flags(t_flags *flags);
void			parse_format(const char **format, t_flags *flags, va_list ap);

// ft_printf_dispatch.c: Function to dispatch based on specifier
int				dispatch_print(t_flags *flags, va_list ap);

// ft_printf_handlers_alpha.c: Handlers for char, string, and pointer
int				handle_char(t_flags *flags, va_list ap);
int				handle_percent(t_flags *flags);
int				handle_string(t_flags *flags, va_list ap);
int				handle_pointer(t_flags *flags, va_list ap);

// ft_printf_alpha_utils.c: Helpers for alphabetic handlers
int				apply_char_padding(char c, t_flags *flags);

/*
 * ============================================================================
 * OS-Specific Handler Prototypes & Macros
 * ============================================================================
*/

// For '%' speicifier
int				handle_percent_macos(t_flags *flags);
int				handle_percent_linux(t_flags *flags);

// For 's' specifier
char			*get_processed_string_and_len_macos(char *str, t_flags *flags,
					size_t *len);
char			*get_processed_string_and_len_linux(char *str, t_flags *flags,
					size_t *len);

// Macro to select the correct function based on OS
# ifdef __APPLE__
#  define IS_LINUX 0
#  define PRINT_NULL_AS_0X0 "0x0"
# else
#  define IS_LINUX 1
#  define PRINT_NULL_AS_0X0 "(nil)"
# endif

// ft_printf_handlers_numeric.c: Handlers for numeric types
int				handle_decimal(t_flags *flags, va_list ap);
int				handle_unsigned(t_flags *flags, va_list ap);
int				handle_hex(t_flags *flags, va_list ap);

// ft_printf_handle_padding.c: Function for padding and final print
int				print_with_padding(char *content, const t_flags *flags);

// ft_printf_utils.c: Utility helper functions
char			*ft_uitoa(unsigned int n);
char			*ft_ultoa_hex(unsigned long nbr, char specifier);

/*
** =============================================================================
**                            ADDED FROM GET_NEXT_LINE
** =============================================================================
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/**
 * @brief Dynamic array data structure for character storage
 * @details This structure implements a resizable array that can dynamically
 *          grow as more data is appended. It's primarily used in get_next_line
 *          to efficiently store and manage the data being read from a file
 *          descriptor without needing to know the size in advance.
 * 
 * @var data     Pointer to the character buffer that holds the array elements
 * @var size     Current number of elements stored in the array
 * @var capacity Total allocated memory capacity of the array in bytes
 * 
 * @note Memory for this structure must be allocated using dynarray_create()
 *       and freed using dynarray_destroy() to prevent memory leaks
 */
typedef struct s_gnl_buffer
{
	char	*data;
	size_t	size;
	size_t	capacity;
}	t_gnl_buffer;

/**
 * @brief Linked list node structure for tracking file descriptors
 * @details This linked list is used to store and manage the reading state 
 *          of multiple file descriptors simultaneously. Each node represents
 *          a unique file descriptor being processed by get_next_line. This 
 *          allows the function to maintain separate buffers and reading 
 *          positions for each file descriptor between consecutive calls.
 * 
 * @var fd      The file descriptor this node is associated with
 * @var buffer  Dynamic array that stores data read from the file descriptor
 *              and maintains the current reading position
 * @var next    Pointer to the next node in the linked list, or NULL if this
 *              is the last node
 * 
 * @note This structure is used internally by get_next_line to implement
 *       handling of multiple file descriptors (bonus requirement)
 */
typedef struct s_gnl_node
{
	int					fd;
	t_gnl_buffer		*buffer;
	struct s_gnl_node	*next;
}	t_gnl_node;

/**
 * @brief Reads and returns the next line from a file descriptor
 * @details This function reads data from the specified file descriptor until 
 *          it encounters a newline character or EOF, then returns the line.
 *          It maintains state between calls using a static linked list,
 *          allowing it to handle multiple file descriptors simultaneously.
 *          Each subsequent call continues reading from where the previous
 *          call left off.
 *
 * @param fd File descriptor to read from
 * @return A newly allocated string containing the next line (including the 
 *         newline character if present), or NULL if:
 *         - the fd is invalid (negative)
 *         - BUFFER_SIZE is invalid (zero or negative)
 *         - memory allocation fails
 *         - an error occurs during reading
 *         - EOF is reached and no more lines are available
 *
 * @note The caller is responsible for freeing the returned string
 * @note This function is designed to be called repeatedly until NULL is 
 * 			returned
 */
char			*get_next_line(int fd);

/**
 * @brief Searches for the first occurrence of a byte in memory
 *
 * This function scans the first n bytes of the memory area pointed to by s
 * for the first occurrence of the byte c (converted to an unsigned char).
 * 
 * @param s Pointer to the memory area to be searched
 * @param c Character to locate (converted to unsigned char)
 * @param n Number of bytes to be analyzed
 * 
 * @return Pointer to the matching byte if found, NULL if not found or if s is 
 *			NULL
 */
void			*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Frees the memory of a dynamic array
 *
 * This function deallocates all memory associated with a dynamic array.
 * It first frees the data area of the array, then frees the array structure 
 * itself. If a NULL pointer is passed, it safely returns without performing 
 * any operation.
 *
 * @param arr Pointer to the dynamic array to be deallocated
 */
void			dynarray_destroy(t_gnl_buffer *arr);

/**
 * @brief Appends data to the end of a dynamic array
 * @details This function adds the specified data to the end of the dynamic 
 * 			array.
 *          If the array's current capacity is insufficient to hold the new 
 * 			data,
 *          it automatically resizes the array. The function copies 'len' bytes
 *          from the source data pointer to the end of the array and updates
 *          the array's size accordingly.
 *
 * @param arr  Pointer to the dynamic array to which data will be appended
 * @param data Pointer to the data to be appended to the array
 * @param len  Number of bytes to append from the data source
 * 
 * @return 1 on successful append, 0 if memory allocation fails or if invalid 
 *         parameters are provided
 *
 * @note This function may reallocate memory if the array needs to grow
 */
int				dynarray_append(t_gnl_buffer *arr, const void *data,
					size_t len);

/**
 * @brief Creates a new dynamic array with specified initial capacity
 *
 * This function allocates memory for a new dynamic array structure and its
 * internal data buffer. The array will be empty initially (size = 0) but
 * will have the specified capacity reserved.
 *
 * @param initial_capacity The initial memory capacity to allocate for the 
 * 							array data
 * @return Pointer to the newly created dynamic array, or NULL if memory 
 * 			allocation fails
 * 
 * @note The caller is responsible for freeing the array using 
 * 			dynarray_destroy()
 */
t_gnl_buffer	*dynarray_create(size_t initial_capacity);

/**
 * @brief Finds or creates a list node for a specific file descriptor
 *
 * This function searches through the linked list for a node with the specified
 * file descriptor. If found, it returns that node. If not found, it creates a 
 * new node with the given file descriptor, initializes it with a dynamic array
 * buffer, and adds it to the front of the list.
 *
 * @param lst Pointer to the head of the linked list
 * @param fd File descriptor to search for or create a node for
 * @return Pointer to the found or newly created node, or NULL if allocation 
 * 			fails or if lst is NULL
 */
t_gnl_node		*gnl_find_or_create_node(t_gnl_node **lst, int fd);

/* ----------------- Additional Utility Functions ----------------- */
int				ft_atoi_base(const char *str, int base);
void			ft_free_split(char **split);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);

#endif

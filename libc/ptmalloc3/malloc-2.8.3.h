/*
  Default header file for malloc-2.8.x, written by Doug Lea
  and released to the public domain, as explained at
  http://creativecommons.org/licenses/publicdomain.

  last update: Mon Aug 15 08:55:52 2005  Doug Lea  (dl at gee)

  This header is for ANSI C/C++ only.  You can set any of
  the following #defines before including:

  // 本头文件只是用于ANSI的c/c++头文件，你可以在引入本头文件后设置任意下面的宏定义：

  * If USE_DL_PREFIX is defined, it is assumed that malloc.c
    was also compiled with this option, so all routines
    have names starting with "dl".

  // 如果 USE_DL_PREFIX 被定义，假定malloc.c也被用此选项编译，那么所有的接口命名将以dl开头。

  * If HAVE_USR_INCLUDE_MALLOC_H is defined, it is assumed that this
    file will be #included AFTER <malloc.h>. This is needed only if
    your system defines a struct mallinfo that is incompatible with the
    standard one declared here.  Otherwise, you can include this file
    INSTEAD of your system system <malloc.h>.  At least on ANSI, all
    declarations should be compatible with system versions

  // 如果 HAVE_USR_INCLUDE_MALLOC_H 被定义，假定本文件将被包含在<malloc.h>之后。
  // 如果你的系统定义了mallinfo结构体，那么他声明在此的mallinfo是不兼容标准的。
  // 除非，你引入本文件来替换你系统的<malloc.h>. 至少所有的声明需要兼容你的系统版本。

  * If MSPACES is defined, declarations for mspace versions are included.

  // 如果 MSPACES 被定义，那么mspace的版本声明需要被引入。
*/

#ifndef MALLOC_280_H
#define MALLOC_280_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h> /* for size_t */

#if !ONLY_MSPACES

#ifndef USE_DL_PREFIX
#define dlcalloc calloc
#define dlfree free
#define dlmalloc malloc
#define dlmemalign memalign
#define dlrealloc realloc
#define dlvalloc valloc
#define dlpvalloc pvalloc
#define dlmallinfo mallinfo
#define dlmallopt mallopt
#define dlmalloc_trim malloc_trim
#define dlmalloc_stats malloc_stats
#define dlmalloc_usable_size malloc_usable_size
#define dlmalloc_footprint malloc_footprint
#define dlindependent_calloc independent_calloc
#define dlindependent_comalloc independent_comalloc
#endif /* USE_DL_PREFIX */

  /*
    malloc(size_t n)
    Returns a pointer to a newly allocated chunk of at least n bytes, or
    null if no space is available, in which case errno is set to ENOMEM
    on ANSI C systems.

    // 返回一个指向至少n字节的新分配的chunk，如果没有空间可用，则返回null，这种情况
    // 在ANSI C 系统里，errno被设置为ENOMEM.

    If n is zero, malloc returns a minimum-sized chunk. (The minimum
    size is 16 bytes on most 32bit systems, and 32 bytes on 64bit
    systems.)  Note that size_t is an unsigned type, so calls with
    arguments that would be negative if signed are interpreted as
    requests for huge amounts of space, which will often fail. The
    maximum supported value of n differs across systems, but is in all
    cases less than the maximum representable value of a size_t.

    // 如果n为零，malloc返回一个最小尺寸的chunk(在大多数32位系统中，最小尺寸是16字节，
    // 64位系统中最小尺寸是32字节。)
    // 注意 size_t 是无符号类型，所以调用参数如果是有符号的负数，将被解释为请求巨大的内存空间。
    // 这通常会失败。
    // 最大支持的值不同的系统不同，但是在所有情况下，都是小于size_t所能表示的最大值。
  */
  void *dlmalloc(size_t);

  /*
    free(void* p)
    Releases the chunk of memory pointed to by p, that had been previously
    allocated using malloc or a related routine such as realloc.
    It has no effect if p is null. If p was not malloced or already
    freed, free(p) will by default cuase the current program to abort.

    // 释放之前用malloc或者关联的如realloc申请的chunk内存(指针p)
    // 如果p为空，他将什么都不做，如果p没有被申请，或者已经被释放，再调用free将自动导致当前程序中止。
  */
  void dlfree(void *);

  /*
    calloc(size_t n_elements, size_t element_size);
    Returns a pointer to n_elements * element_size bytes, with all locations
    set to zero.

    // 返回一个n_elements * element_size字节的指针，并且这些区域被设置为零。
  */
  void *dlcalloc(size_t, size_t);

  /*
    realloc(void* p, size_t n)
    Returns a pointer to a chunk of size n that contains the same data
    as does chunk p up to the minimum of (n, p's size) bytes, or null
    if no space is available.

    // 返回n个字节的chunk的指针，并且包含了原来p所指向的相同的数据，数据尺寸在n和p的尺寸取最小值。
    // 如果没有可用空间可用，返回null.

    The returned pointer may or may not be the same as p. The algorithm
    prefers extending p in most cases when possible, otherwise it
    employs the equivalent of a malloc-copy-free sequence.

    // 返回的指针和原来的p指针可能相同，也可能不同。算法倾向于在大多数可能情况下扩展p，
    // 否则执行等价的malloc-copy-free操作。

    If p is null, realloc is equivalent to malloc.

    // 如果p是空，realloc等价于malloc

    If space is not available, realloc returns null, errno is set (if on
    ANSI) and p is NOT freed.

    // 如果空间不可用，realloc返回空，errno将被设置，同时p不会被释放。

    if n is for fewer bytes than already held by p, the newly unused
    space is lopped off and freed if possible.  realloc with a size
    argument of zero (re)allocates a minimum-sized chunk.

    // 如果n小于p所指向的内存大小，新的未被使用的空间将被删除并释放。
    // 尺寸为0的参数调用realloc，将申请一个最小尺寸的chunk.

    The old unix realloc convention of allowing the last-free'd chunk
    to be used as an argument to realloc is not supported.

    // 旧的unix，realloc允许的规定：不支持最近释放的chunk被用做realloc参数。
  */

  void *dlrealloc(void *, size_t);

  /*
    memalign(size_t alignment, size_t n);
    Returns a pointer to a newly allocated chunk of n bytes, aligned
    in accord with the alignment argument.

    // 返回一个新申请的n字节的chunk指针。指针是根据alignmeng参数对齐的。

    The alignment argument should be a power of two. If the argument is
    not a power of two, the nearest greater power is used.
    8-byte alignment is guaranteed by normal malloc calls, so don't
    bother calling memalign with an argument of 8 or less.

    // alignmeng参数应该是2的幂。如果不是2的幂，那么将使用大于该值的最近的2的幂。
    // 通常malloc调用8字节对齐时必然的。所以不要用小于等于8的对齐参数调用memalign。

    Overreliance on memalign is a sure way to fragment space.
    // 过度信赖memalign将确定会造成空间(内存)碎片。
    //
  */
  void *dlmemalign(size_t, size_t);

  /*
    valloc(size_t n);
    Equivalent to memalign(pagesize, n), where pagesize is the page
    size of the system. If the pagesize is unknown, 4096 is used.

    // 等价于memalign(页面大小, n), 页面大小即为系统的页面大小，如果不知道页面大小是未知的，则用4096(默认)。

  */
  void *dlvalloc(size_t);

  /*
    mallopt(int parameter_number, int parameter_value)
    Sets tunable parameters The format is to provide a
    (parameter-number, parameter-value) pair.  mallopt then sets the
    corresponding parameter to the argument value if it can (i.e., so
    long as the value is meaningful), and returns 1 if successful else
    0.  SVID/XPG/ANSI defines four standard param numbers for mallopt,
    normally defined in malloc.h.  None of these are use in this malloc,
    so setting them has no effect. But this malloc also supports other
    options in mallopt:

    // 设置可调参数，提供的格式为参数key-value对。mallopt设置相应的参数对应的参数值
    // 成功返回1，失败返回0。SVID/XPG/ANSI 为mallopt定义四个标准参数key，通常在malloc.h中定义。
    // 在当前malloc，这些是没有被使用，所以设置他们没有任何效果。但是当前malloc也支持其他的选项:

    Symbol            param #  default    allowed param values
    M_TRIM_THRESHOLD     -1   2*1024*1024   any   (-1U disables trimming)
    M_GRANULARITY        -2     page size   any power of 2 >= page size
    M_MMAP_THRESHOLD     -3      256*1024   any   (or 0 if no MMAP support)
  */
  int dlmallopt(int, int);

#define M_TRIM_THRESHOLD (-1)
#define M_GRANULARITY (-2)
#define M_MMAP_THRESHOLD (-3)

  /*
    malloc_footprint();
    Returns the number of bytes obtained from the system.  The total
    number of bytes allocated by malloc, realloc etc., is less than this
    value. Unlike mallinfo, this function returns only a precomputed
    result, so can be called frequently to monitor memory consumption.
    Even if locks are otherwise defined, this function does not use them,
    so results might not be up to date.

    // 返回从系统获取的字节数。通过malloc/realloc/...等等申请的总字节数，小于这个值。
    // 不像mallinfo，这个函数返回一个预先计算的结果: 所以能被频繁调用，去监控内存消耗。
    // 甚至锁都不被定义，这个函数并不使用他们，所以结果可能不是最新的。
  */
  size_t dlmalloc_footprint(void);

#if !NO_MALLINFO
/*
  mallinfo()
  Returns (by copy) a struct containing various summary statistics:

  // 通过拷贝的方式返回一个结构体，包含了各种各样的概要统计。

  arena:     current total non-mmapped bytes allocated from system
  ordblks:   the number of free chunks
  smblks:    always zero.
  hblks:     current number of mmapped regions
  hblkhd:    total bytes held in mmapped regions
  usmblks:   the maximum total allocated space. This will be greater
                than current total if trimming has occurred.
  fsmblks:   always zero
  uordblks:  current total allocated space (normal or mmapped)
  fordblks:  total free space
  keepcost:  the maximum number of bytes that could ideally be released
               back to system via malloc_trim. ("ideally" means that
               it ignores page restrictions etc.)

  // arena:    当前总共从系统申请的非映射的字节
  // ordblks:  空闲chunks数
  // smblks:   通常为零
  // hblks:    当前映射区域数。
  // hblkhd:   映射区域持有的综字节数。
  // usmblks:  最大总申请空间。当trim发生的时候，这个数将大于当前总数。
  // fsmblks:  通常为零
  // uordblks: 当前总共申请空间(正常或映射的)
  // fordblks: 总空闲数
  // keepcost: 最大字节数：通过malloc_trim能够被理想地释放并返回给系统的字节数，理想意味着忽略页面限制规定等。

  Because these fields are ints, but internal bookkeeping may
  be kept as longs, the reported values may wrap around zero and
  thus be inaccurate.

  // 因为这些域是整型，但是内部的记账可能保存为long，被记录的值可能被零环绕而因此不准确。
*/
#ifndef HAVE_USR_INCLUDE_MALLOC_H
#ifndef _MALLOC_H
#ifndef MALLINFO_FIELD_TYPE
#define MALLINFO_FIELD_TYPE size_t
#endif /* MALLINFO_FIELD_TYPE */
  struct mallinfo
  {
    MALLINFO_FIELD_TYPE arena;    /* non-mmapped space allocated from system */
    MALLINFO_FIELD_TYPE ordblks;  /* number of free chunks */
    MALLINFO_FIELD_TYPE smblks;   /* always 0 */
    MALLINFO_FIELD_TYPE hblks;    /* always 0 */
    MALLINFO_FIELD_TYPE hblkhd;   /* space in mmapped regions */
    MALLINFO_FIELD_TYPE usmblks;  /* maximum total allocated space */
    MALLINFO_FIELD_TYPE fsmblks;  /* always 0 */
    MALLINFO_FIELD_TYPE uordblks; /* total allocated space */
    MALLINFO_FIELD_TYPE fordblks; /* total free space */
    MALLINFO_FIELD_TYPE keepcost; /* releasable (via malloc_trim) space */
  };
#endif /* _MALLOC_H */
#endif /* HAVE_USR_INCLUDE_MALLOC_H */

  struct mallinfo dlmallinfo(void);
#endif /* NO_MALLINFO */

  /*
    independent_calloc(size_t n_elements, size_t element_size, void* chunks[]);

    independent_calloc is similar to calloc, but instead of returning a
    single cleared space, it returns an array of pointers to n_elements
    independent elements that can hold contents of size elem_size, each
    of which starts out cleared, and can be independently freed,
    realloc'ed etc. The elements are guaranteed to be adjacently
    allocated (this is not guaranteed to occur with multiple callocs or
    mallocs), which may also improve cache locality in some
    applications.

    // independent_calloc和calloc相似, 但并不是返回的是单一的被清理的空间。它返回一个指向n_elements个独立元素的数组。
    // 独立元素持有elem_size大小的内容，每一个都从清理开始，并且能被独立的释放、重新申请等。
    // 这些元素能够保证被连续申请(多次calloc或者malloc并不保证连续)，在一些应用中能够改善本地缓存。

    The "chunks" argument is optional (i.e., may be null, which is
    probably the most typical usage). If it is null, the returned array
    is itself dynamically allocated and should also be freed when it is
    no longer needed. Otherwise, the chunks array must be of at least
    n_elements in length. It is filled in with the pointers to the
    chunks.

    // chunks参数是可选的(例如，可以为空，或许这是最经典的使用方式)。
    // 如果他为空，返回的数组是动态申请的，并且当他不在使用的时候应该也能被free。
    // 否则，chunks数组长度必须是至少n_element。并且被指向chunks的指针填充。

    In either case, independent_calloc returns this pointer array, or
    null if the allocation failed.  If n_elements is zero and "chunks"
    is null, it returns a chunk representing an array with zero elements
    (which should be freed if not wanted).

    // 无论那种情况，indepdent_calloc返回指针数组，或者当申请失败的时候返回空。
    // 如果n_elements是0并且chunks是空，它返回一个chunk：一个含有0个元素的数组(如果不是所要的，应该要释放)

    Each element must be individually freed when it is no longer
    needed. If you'd like to instead be able to free all at once, you
    should instead use regular calloc and assign pointers into this
    space to represent elements.  (In this case though, you cannot
    independently free elements.)

    // 每一个element当不再需要的时候，必须呗独立的释放。
    // 如果你愿意，也能一次释放所有。你应该使用规范的calloc并且分配指针-指向elements的空间。
    // (尽管在这种情况，你不能独立的释放elements)

    independent_calloc simplifies and speeds up implementations of many
    kinds of pools.  It may also be useful when constructing large data
    structures that initially have a fixed number of fixed-sized nodes,
    but the number is not known at compile time, and some of the nodes
    may later need to be freed. For example:

    // independent_calloc简化并且加快了各种池化的实现。
    // 这种情况或许也是有用的：当构造大的数据结构，这些数据结构用一个固定数量的固定大小的节点初始化，
    // 并且这个数量在编译时并不知道，并且一些节点会延迟释放，如下：

    struct Node { int item; struct Node* next; };

    struct Node* build_list() {
      struct Node** pool;
      int n = read_number_of_nodes_needed();
      if (n <= 0) return 0;
      pool = (struct Node**)(independent_calloc(n, sizeof(struct Node), 0);
      if (pool == 0) die();
      // organize into a linked list...
      struct Node* first = pool[0];
      for (i = 0; i < n-1; ++i)
        pool[i]->next = pool[i+1];
      free(pool);     // Can now free the array (or not, if it is needed later)
      return first;
    }
  */
  void **dlindependent_calloc(size_t, size_t, void **);

  /*
    independent_comalloc(size_t n_elements, size_t sizes[], void* chunks[]);

    independent_comalloc allocates, all at once, a set of n_elements
    chunks with sizes indicated in the "sizes" array.    It returns
    an array of pointers to these elements, each of which can be
    independently freed, realloc'ed etc. The elements are guaranteed to
    be adjacently allocated (this is not guaranteed to occur with
    multiple callocs or mallocs), which may also improve cache locality
    in some applications.

    // independent_comalloc 一次性返回 一个n_elements的集合，每个都大小都在sizes数组里面指定。
    // 他返回了一个数组指针，指向了这些元素，每个都能被独立的释放，重新申请等。
    // 这些元素确保被连续申请(多次calloc或者malloc并不保证连续)，在一些应用中能够改善本地缓存。

    The "chunks" argument is optional (i.e., may be null). If it is null
    the returned array is itself dynamically allocated and should also
    be freed when it is no longer needed. Otherwise, the chunks array
    must be of at least n_elements in length. It is filled in with the
    pointers to the chunks.

    In either case, independent_comalloc returns this pointer array, or
    null if the allocation failed.  If n_elements is zero and chunks is
    null, it returns a chunk representing an array with zero elements
    (which should be freed if not wanted).

    Each element must be individually freed when it is no longer
    needed. If you'd like to instead be able to free all at once, you
    should instead use a single regular malloc, and assign pointers at
    particular offsets in the aggregate space. (In this case though, you
    cannot independently free elements.)

    independent_comallac differs from independent_calloc in that each
    element may have a different size, and also that it does not
    automatically clear elements.

    independent_comalloc can be used to speed up allocation in cases
    where several structs or objects must always be allocated at the
    same time.  For example:

    struct Head { ... }
    struct Foot { ... }

    void send_message(char* msg) {
      int msglen = strlen(msg);
      size_t sizes[3] = { sizeof(struct Head), msglen, sizeof(struct Foot) };
      void* chunks[3];
      if (independent_comalloc(3, sizes, chunks) == 0)
        die();
      struct Head* head = (struct Head*)(chunks[0]);
      char*        body = (char*)(chunks[1]);
      struct Foot* foot = (struct Foot*)(chunks[2]);
      // ...
    }

    In general though, independent_comalloc is worth using only for
    larger values of n_elements. For small values, you probably won't
    detect enough difference from series of malloc calls to bother.

    Overuse of independent_comalloc can increase overall memory usage,
    since it cannot reuse existing noncontiguous small chunks that
    might be available for some of the elements.
  */
  void **dlindependent_comalloc(size_t, size_t *, void **);

  /*
    pvalloc(size_t n);
    Equivalent to valloc(minimum-page-that-holds(n)), that is,
    round up n to nearest pagesize.
   */
  void *dlpvalloc(size_t);

  /*
    malloc_trim(size_t pad);

    If possible, gives memory back to the system (via negative arguments
    to sbrk) if there is unused memory at the `high' end of the malloc
    pool or in unused MMAP segments. You can call this after freeing
    large blocks of memory to potentially reduce the system-level memory
    requirements of a program. However, it cannot guarantee to reduce
    memory. Under some allocation patterns, some large free blocks of
    memory will be locked between two used chunks, so they cannot be
    given back to the system.

    The `pad' argument to malloc_trim represents the amount of free
    trailing space to leave untrimmed. If this argument is zero, only
    the minimum amount of memory to maintain internal data structures
    will be left. Non-zero arguments can be supplied to maintain enough
    trailing space to service future expected allocations without having
    to re-obtain memory from the system.

    Malloc_trim returns 1 if it actually released any memory, else 0.
  */
  int dlmalloc_trim(size_t);

  /*
    malloc_usable_size(void* p);

    Returns the number of bytes you can actually use in
    an allocated chunk, which may be more than you requested (although
    often not) due to alignment and minimum size constraints.
    You can use this many bytes without worrying about
    overwriting other allocated objects. This is not a particularly great
    programming practice. malloc_usable_size can be more useful in
    debugging and assertions, for example:

    p = malloc(n);
    assert(malloc_usable_size(p) >= 256);
  */
  size_t dlmalloc_usable_size(void *);

  /*
    malloc_stats();
    Prints on stderr the amount of space obtained from the system (both
    via sbrk and mmap), the maximum amount (which may be more than
    current if malloc_trim and/or munmap got called), and the current
    number of bytes allocated via malloc (or realloc, etc) but not yet
    freed. Note that this is the number of bytes allocated, not the
    number requested. It will be larger than the number requested
    because of alignment and bookkeeping overhead. Because it includes
    alignment wastage as being in use, this figure may be greater than
    zero even when no user-level chunks are allocated.

    The reported current and maximum system memory can be inaccurate if
    a program makes other calls to system memory allocation functions
    (normally sbrk) outside of malloc.

    malloc_stats prints only the most commonly interesting statistics.
    More information can be obtained by calling mallinfo.
  */
  void dlmalloc_stats(void);

#endif /* !ONLY_MSPACES */

#if MSPACES

  /*
    mspace is an opaque type representing an independent
    region of space that supports mspace_malloc, etc.
  */
  typedef void *mspace;

  /*
    create_mspace creates and returns a new independent space with the
    given initial capacity, or, if 0, the default granularity size.  It
    returns null if there is no system memory available to create the
    space.  If argument locked is non-zero, the space uses a separate
    lock to control access. The capacity of the space will grow
    dynamically as needed to service mspace_malloc requests.  You can
    control the sizes of incremental increases of this space by
    compiling with a different DEFAULT_GRANULARITY or dynamically
    setting with mallopt(M_GRANULARITY, value).
  */
  mspace create_mspace(size_t capacity, int locked);

  /*
    destroy_mspace destroys the given space, and attempts to return all
    of its memory back to the system, returning the total number of
    bytes freed. After destruction, the results of access to all memory
    used by the space become undefined.
  */
  size_t destroy_mspace(mspace msp);

  /*
    create_mspace_with_base uses the memory supplied as the initial base
    of a new mspace. Part (less than 128*sizeof(size_t) bytes) of this
    space is used for bookkeeping, so the capacity must be at least this
    large. (Otherwise 0 is returned.) When this initial space is
    exhausted, additional memory will be obtained from the system.
    Destroying this space will deallocate all additionally allocated
    space (if possible) but not the initial base.
  */
  mspace create_mspace_with_base(void *base, size_t capacity, int locked);

  /*
    mspace_malloc behaves as malloc, but operates within
    the given space.
  */
  void *mspace_malloc(mspace msp, size_t bytes);

  /*
    mspace_free behaves as free, but operates within
    the given space.

    If compiled with FOOTERS==1, mspace_free is not actually needed.
    free may be called instead of mspace_free because freed chunks from
    any space are handled by their originating spaces.
  */
  void mspace_free(mspace msp, void *mem);

  /*
    mspace_realloc behaves as realloc, but operates within
    the given space.

    If compiled with FOOTERS==1, mspace_realloc is not actually
    needed.  realloc may be called instead of mspace_realloc because
    realloced chunks from any space are handled by their originating
    spaces.
  */
  void *mspace_realloc(mspace msp, void *mem, size_t newsize);

  /*
    mspace_calloc behaves as calloc, but operates within
    the given space.
  */
  void *mspace_calloc(mspace msp, size_t n_elements, size_t elem_size);

  /*
    mspace_memalign behaves as memalign, but operates within
    the given space.
  */
  void *mspace_memalign(mspace msp, size_t alignment, size_t bytes);

  /*
    mspace_independent_calloc behaves as independent_calloc, but
    operates within the given space.
  */
  void **mspace_independent_calloc(mspace msp, size_t n_elements,
                                   size_t elem_size, void *chunks[]);

  /*
    mspace_independent_comalloc behaves as independent_comalloc, but
    operates within the given space.
  */
  void **mspace_independent_comalloc(mspace msp, size_t n_elements,
                                     size_t sizes[], void *chunks[]);

  /*
    mspace_footprint() returns the number of bytes obtained from the
    system for this space.
  */
  size_t mspace_footprint(mspace msp);

#if !NO_MALLINFO
  /*
    mspace_mallinfo behaves as mallinfo, but reports properties of
    the given space.
  */
  struct mallinfo mspace_mallinfo(mspace msp);
#endif /* NO_MALLINFO */

  /*
    mspace_malloc_stats behaves as malloc_stats, but reports
    properties of the given space.
  */
  void mspace_malloc_stats(mspace msp);

  /*
    mspace_trim behaves as malloc_trim, but
    operates within the given space.
  */
  int mspace_trim(mspace msp, size_t pad);

  /*
    An alias for malloc_usable_size.
  */
  size_t mspace_usable_size(void *mem);

  /*
    An alias for mallopt.
  */
  int mspace_mallopt(int, int);

#endif /* MSPACES */

#ifdef __cplusplus
}; /* end of extern "C" */
#endif

#endif /* MALLOC_280_H */

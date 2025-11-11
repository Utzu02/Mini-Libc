# Mini-libc Snapshot

This repository contains a self-contained, syscall-only C standard library subset that can replace glibc for simple workloads on Linux/x86_64. The focus is on features I actually implemented: string manipulation, memory allocation based on `mmap`, low-level file I/O, and basic sleep helpers. Everything is built as a static archive (`libc.a`) that applications can link against.

## Highlights

- **String & memory suite** – `strcpy`, `strcat`, `strlen`, `strncpy`, `strncat`, `strcmp`, `strncmp`, `strstr`, `strrstr`, `memcpy`, `memset`, `memmove`, and `memcmp` are implemented manually in `src/string/string.c`.
- **Memory allocator** – `malloc`, `calloc`, `realloc`, `reallocarray`, `free`, plus the raw `mmap`, `mremap`, `munmap` wrappers, live under `src/mm`. Allocations grab anonymous pages via `mmap`, stash the block size in a header word, and unmap on `free`.
- **I/O syscalls** – `open`, `close`, `lseek`, `truncate`, `ftruncate`, `stat`, `fstat`, `fstatat`, and `puts` wrap the corresponding Linux syscalls, translate negative returns into `errno`, and never depend on glibc.
- **Sleep helpers** – `nanosleep` is a thin syscall wrapper; `sleep` builds a `timespec`, calls `nanosleep`, and returns the remaining seconds if interrupted. A lightweight `time.h` header and `time_t` typedef back these APIs.
- **Build glue** – `src/Makefile` archives all sources (including the new `io/puts.c` and `process/*.c`) into `libc.a`, so `make` inside `src/` is enough to produce the library.

## Architecture At A Glance

| Area | Files | Notes |
| --- | --- | --- |
| String helpers | `src/string/string.c` | Pointer-based loops only; no external dependencies. |
| Syscall layer | `src/internal/arch/x86_64/syscall_arch.h`, `src/syscall.c` | Shared helper used by every wrapper. |
| Memory allocation | `src/mm/malloc.c`, `src/mm/mmap.c`, `include/internal/mm/mem_list.h` | Simple header-before-payload layout; no free list yet. |
| Low-level I/O | `src/io/*.c`, `src/stat/*.c` | Names and signatures mirror the POSIX headers in `src/include`. |
| Process utilities | `src/process/nanosleep.c`, `src/process/sleep.c` | Provide blocking sleeps without signals helpers. |

## Building

```sh
cd src
make
```

This produces `libc.a`. You can link it by passing `-Lsrc -l:libc.a` (or copying the archive alongside your program and linking with `-lmini` etc.).

## Testing

```sh
cd tests
make check      # run the mini test-suite
./run_all_tests.sh
```

Scripts invoke the compiled objects directly, so make sure `src/libc.a` exists before running them. The tests exercise every function mentioned in the Highlights section (string, I/O, memory, mmap, sleep).

For grading we rely on the upstream Docker checker image (`checker/` directory). Running `docker-compose run checker` (or `./checker/checker-docker.sh` if provided by your environment) is the recommended path because it bundles all required linters and toolchain versions, avoiding host-specific issues.

### Docker Checker (full workflow)

This is the official way to grade: it uses the provided Docker container for a stable toolchain and an isolated environment that matches the CI runners. Follow the same steps the initial README recommended:

1. Ensure Docker is installed on your machine (see https://docs.docker.com/engine/install/).
2. Use the helper script from the repo root to build the image:

   ```console
   ./local.sh docker build
   ```

   The script tags the image as `gitlab.cs.pub.ro:5050/operating-systems/assignment-mini-libc:latest`, matching the remote runner.

3. Launch the checker inside the container:

   ```console
   ./local.sh checker
   ```

   This runs `checker/checker.sh`, which first compiles/tests everything under `tests/`, then executes the linters (`checkpatch`, `cpplint`, `shellcheck`) using the configs shipped in the repo.

4. (Optional) Push to your fork to trigger the exact same pipeline remotely. GitLab CI runs the checker inside the same image, so the local results and CI results stay in sync.

If you need the long-form version (including Moodle submission details), see `README.checker.md` or the VMChecker Student Handbook linked there.

## File Map

- `src/include/` – Headers that mirror the public API (`stdio.h`, `string.h`, `time.h`, etc.).
- `src/io/` – Thin syscall wrappers for file descriptors, plus `puts`.
- `src/mm/` – The allocator and mmap helpers.
- `src/process/` – Sleep-related functionality.
- `tests/` – Shell scripts and small programs that validate each API.
- `samples/` – Simple demo programs that link against `libc.a`.

That's the entire scope: a compact libc subset implemented purely with Linux syscalls, ready to drop into small projects or educational experiments.

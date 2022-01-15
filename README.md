Dependencies: scons, python3

You can run a clang-tidy check via `scripts/clang-tidy.sh` from the root of the
repository.

# Formatting

We use `clang-format` for C++ code formatting. To format all files, you can run
the following from the repository root:

``` find -name "*.hpp" -or -name "*.cpp" | xargs clang-format -i ```

Alternatively, if you use `vim`, you can [configure
it](https://github.com/n-samar/.config/blob/master/nvim/init.vim#L126-L128) to
format on each save.  The linked configuration uses `rhysd/vim-clang-format` to
`clang-format` on each save all `*.c`, `*.h`, `*.cpp`, `*.hpp` files, but only
when a `.clang-format` file exists in the path of the file being saved; the
formatting is done by the rules specified in this `.clang-format` file.

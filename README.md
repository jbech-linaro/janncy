Dependencies: scons, python3, clang-10

# Pre-Commit Hooks
Install [pre-commit] to automatically run the pre-commit hooks before comitting.
To run the hooks manually, use
```bash
$ pre-commit run --all-files
```

# Style and Formatting
We defer all formatting and style decisions to the [Google C++ Style
Guide][google-cpp].

We use [clang-format] for C++ code formatting.
Clang-format should be executed automatically by a pre-commit hook.

Additionally, if you use `vim`, you can [configure it][clang-format-vimrc] to
run clang-format when a C++ file is saved. The linked configuration uses
[rhysd/vim-clang-format][vim-clang-format], and follows the rules specified in
`.clang-format` (and doesn't run if `.clang-format` doesn't exist).

You can also try running a clang-tidy check via `scripts/clang-tidy.sh` from the
root of the repository, but that's not yet super reliable.

[pre-commit]: https://pre-commit.com/
[google-cpp]: https://google.github.io/styleguide/cppguide.html
[clang-format]: https://clang.llvm.org/docs/ClangFormat.html
[clang-format-vimrc]: https://github.com/n-samar/.config/blob/master/nvim/init.vim#L126-L128
[vim-clang-format]: https://github.com/rhysd/vim-clang-format

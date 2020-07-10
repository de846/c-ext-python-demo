from distutils.core import setup, Extension


def main():
    setup(
        name="fputs",
        version="1.0",
        description="Python module interface for fputs in C",
        author="David Ecker",
        author_email="dahveed311@gmail.com",
        ext_modules=[Extension("fputs", ["fputs_module.c"])]
    )


if __name__ == "__main__":
    main()

void printHelp(){
    printf("Usage: opensnap <OPTION>\n");
    printf("\n");
    printf("Options:\n");
    printf("\n");
    printf("  -d, --daemon                     run opensnap as daemon\n");
    printf("  -o, --offset <PIXEL>             set offset in pixel\n");
    printf("  -t, --threshold <MSECONDS>       set threshold in microseconds\n");
    printf("  -s, --script <PATH>              set script path to <PATH>\n");
    printf("  -v, --verbose                    be verbose\n");
    printf("  -V, --version                    show version\n");
    printf("  -h, --help                       print this help\n");
    printf("\n");
    printf("Example:\n");
    printf("\n");
    printf("opensnap -d -s /etc/opensnap\n");
}

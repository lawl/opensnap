void printHelp(){
    printf("Usage: opensnap <OPTION>\n");
    printf("\n");
    printf("Options:\n");
    printf("\n");
    printf("  -c, --config <PATH>        set your config path to <PATH>\n");
    printf("  -d, --daemon               run opensnap as daemon\n");
    printf("  -o, --offset <PIXEL>       offset in pixel\n");
    printf("  -v, --verbose              be verbose\n");
    printf("  -h, --help                 print this help\n");
    printf("\n");
    printf("Example:\n");
    printf("\n");
    printf("opensnap -c /etc/opensnap -d\n");
}

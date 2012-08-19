void printHelp(){
    printf("Hello, it seems you're struggling with using this program.\n");
    printf("Let me try to be of assistance. First let me show you the valid command line switches.\n\n");
    printf("     -c <path>      set your config path to a different directory. The default path\n");
    printf("                    opensnap is looking for configs is ´~/.config/opensnap´.\n");
    printf("     -d             Run opensnap as daemon.\n");
    printf("     -v             Be verbose.\n");
    printf("     -h             Print this help.\n");
    printf("If this is the first time you run opensnap it's highly recommended to copy the config\n");
    printf("files that came along with this program to your home directory. You'll need to set\n");
    printf("some values before everything works.\n");
    printf("                   mkdir -p ~/.config/opensnap\n");
    printf("                   cp sample_configs/* ~/.config/opensnap/\n");
}

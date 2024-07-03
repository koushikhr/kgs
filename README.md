nix flake update

nix develop

cd src/

```bash
gcc $( pkg-config --cflags gtk4 gtk4-layer-shell-0 ) main.c widgets/bar/bar.c widgets/bar/levelBar.c widgets/bar/services/battery
Status.c -o output $( pkg-config --libs gtk4 gtk4-layer-shell-0 )
```
./output

/*
To enter DEV-Environment = {
    nix develop                                                                         # --- Entering dev shell with required pkgs
    cd src/                                                                             # --- enter src dir to compile and exec
    gcc $( pkg-config --cflags gtk4 ) -o widget widget.c $( pkg-config --libs gtk4 )    # --- To Compile c-program
    ./widget                                                                            # --- To Run Widget
  };
*/
{
  description = "Bar - Using GTK Layer Shell";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils = {
      inputs.nixpkgs.follows = "nixpkgs";
      url = "github:numtide/flake-utils";
    };
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    ...
  } @ inputs:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {inherit system;};
      in rec {
        defaultApp = apps.kgs;
        defaultPackage = packages.kgs;
        devShell = packages.kgs.overrideAttrs (prev: {
          buildInputs = with pkgs;
            prev.buildInputs
            ++ [
              # needed for clangd lsp integration
              (runCommand "cDependencies" {} ''
                mkdir -p $out/include
                cp -r ${gtk4.dev}/include/gtk-4.0/* $out/include
                cp -r ${glib.dev}/include/glib-2.0/* $out/include
              '')
            ];
          shellHook = ''
            NIX_CFLAGS_COMPILE="$(pkg-config --cflags gtk4) $NIX_CFLAGS_COMPILE"
          '';
        });

        apps.kgs = {
          type = "app";
          program = "${defaultPackage}/bin/kgs";
        };
        packages.kgs = pkgs.stdenv.mkDerivation {
          name = "kgs";
          pname = "kgs";
          version = "1.0";
          src = ./src;

          nativeBuildInputs = [pkgs.pkg-config];
          buildInputs = with pkgs; [
            gtk4
            glib
            gtk4-layer-shell
          ];
          buildPhase = ''
            NIX_CFLAGS_COMPILE="$(pkg-config --cflags gtk4) $NIX_CFLAGS_COMPILE"
          '';
          makeFlags = [
            "DESTDIR=$(out)"
          ];
        };
      }
    );
}

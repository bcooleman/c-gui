{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.SDL2
    pkgs.SDL2_ttf
    pkgs.pkg-config
  ];

  shellHook = ''
    echo "Environment ready. You can start developing with SDL2."
  '';
}

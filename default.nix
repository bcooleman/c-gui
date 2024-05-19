{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.SDL2
    pkgs.SDL2_ttf
    pkgs.pkg-config  # Updated from pkgconfig to pkg-config
    pkgs.makeWrapper
  ];

  shellHook = ''
    export SDL2_TTF_LIBS="-L${pkgs.SDL2_ttf}/lib -lSDL2_ttf"
    export SDL2_TTF_CFLAGS="-I${pkgs.SDL2_ttf}/include/SDL2"
  '';
}

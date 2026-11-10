# ps2-hello
Paso 1 del port de Isaac a PS2: comprobar que el toolchain compila y que el .elf corre.

## Compilar desde el navegador
**Opción A (recomendada): GitHub Actions.** Subí estos archivos a un repo nuevo. En la pestaña
Actions corre "build-ps2" solo; al terminar, bajá el artifact `hello-elf` (trae `hello.elf`).

**Opción B: Codespaces.** Code → Codespaces → Create. Abre con la imagen ps2dev; en la terminal: `make`.
Si Codespaces no logra levantar la imagen (es Alpine), usá la opción A.

## Probar
PCSX2 → System → Boot ELF → `hello.elf`. Tiene que verse un cuadrado rojo rebotando.

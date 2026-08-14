# Mapas de teste

Rode sempre a partir da **raiz do projeto** (os caminhos das texturas nos `.cub`
são relativos ao diretório de execução):

```sh
./cub3D maps/valid/simple.cub
```

## Válidos (`maps/valid/`) — devem abrir a janela

| Mapa | O que cobre |
|---|---|
| `simple.cub` | mapa mínimo retangular, spawn `N` |
| `pillars.cub` | paredes internas / câmaras, spawn `S` |
| `irregular.cub` | bordas dentadas (larguras variando), spawn `E` |
| `big.cub` | mapa grande 80×40 com pilares, spawn `N` |
| `huge.cub` | mapa **muito grande** 500×250 (125k células) com pilares, spawn `N` — teste de stress |

## Inválidos (`maps/invalid/`) — devem imprimir `Error` + motivo

| Mapa | Mensagem esperada |
|---|---|
| `not_enclosed.cub` | Map is not enclosed |
| `no_player.cub` | Player spawn not found |
| `multi_player.cub` | Multiple spawn points |
| `invalid_char.cub` | Invalid characters |
| `missing_texture.cub` | Missing texture path |
| `duplicate_texture.cub` | Duplicate texture |
| `missing_color.cub` | Missing ceiling texture |
| `duplicate_color.cub` | Duplicate floor color |
| `invalid_rgb.cub` | Invalid floor color (componente > 255) |
| `bad_texture_path.cub` | Failed to load texture (`.xpm` inexistente) |
| `unknown_id.cub` | Unknown header identifier |
| `no_map.cub` | Couldn't find map |
| `junk_after_map.cub` | Junk found after map ended |

## Limitações conhecidas do parser (a revisar)

- Linhas de mapa **não podem começar com espaço** — o parser trata qualquer linha
  iniciada por espaço como linha de header (`is_header_line`). Por isso os mapas
  válidos aqui não têm indentação à esquerda.

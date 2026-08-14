# Raycasting com DDA — guia de estudo (cub3D)

Este documento explica o algoritmo **DDA** (Digital Differential Analyzer) que
usamos pra desenhar as paredes do cub3D, do zero até o código do projeto.

---

## 1. O problema

No raycasting a gente lança **um raio por coluna da tela** (1280 raios) a partir
do jogador e precisa descobrir, pra cada raio:

1. **Quão longe** está a parede que ele atinge → define a **altura** da parede na tela.
2. **Qual face** da parede foi atingida (Norte/Sul/Leste/Oeste) → escolhe a textura.
3. **Onde exatamente** na parede ele bateu (`wall_x`) → escolhe a **coluna da textura**.

O mapa é uma grade de células de `BLOCK` pixels (aqui `BLOCK = 64`). Parede = `'1'`.

---

## 2. Por que não o "ray-marcher"

A primeira versão andava com o raio de **1 pixel por vez**:

```c
while (!touch(p.x, p.y, game))
{
    p.x += cos(angle);
    p.y += sin(angle);
}
```

Funciona, mas tem 3 defeitos:

- **Impreciso:** quando detecta a parede, o raio já "passou" da borda até ~1px.
  Esse erro, esticado pela perspectiva, vira **costuras** na textura.
- **Ambíguo nos cantos:** perto do canto de um bloco, `x` e `y` cruzam a grade quase
  no mesmo passo → a detecção de face fica instável → amostra a **textura errada**
  (foi o que gerou as linhas pontilhadas coloridas).
- **Lento:** dá centenas de passos até achar a parede.

O DDA resolve os três de uma vez.

---

## 3. A ideia central do DDA

Em vez de andar às cegas, o DDA **pula direto de uma linha da grade pra próxima**.

Pensa numa grade. Um raio saindo do jogador cruza:
- linhas **verticais** (`x = 0, 1, 2, ...` em células), e
- linhas **horizontais** (`y = 0, 1, 2, ...`).

O DDA, a cada passo, pergunta: **qual a próxima linha mais perto — a vertical ou a
horizontal?** Ele pula pra essa e avança a célula naquele eixo. Repete até cair
numa célula de parede.

A grande sacada: **a última linha que ele cruzou diz exatamente a face**:
- cruzou linha vertical por último → parede **vertical** (Leste/Oeste)
- cruzou linha horizontal por último → parede **horizontal** (Norte/Sul)

Zero ambiguidade. É isso que mata as costuras.

> A partir daqui trabalhamos em **unidades de célula** (1 célula = `BLOCK`).
> Converte no fim multiplicando por `BLOCK`.

---

## 4. As variáveis

Para um raio de direção `dir = (cos θ, sin θ)` saindo de `pos` (em células):

| Variável | Significado |
|---|---|
| `pos` | posição do jogador em células (`world / BLOCK`) |
| `dir` | direção do raio, `(cos θ, sin θ)` |
| `map_x, map_y` | célula atual, `floor(pos)` |
| `delta.x` | distância que o raio anda pra cruzar **uma célula inteira em x** = `|1/dir.x|` |
| `delta.y` | idem em y = `|1/dir.y|` |
| `step_x` | +1 ou -1: pra que lado andamos em x |
| `side_dist.x` | distância do `pos` até a **próxima** linha vertical |
| `side_dist.y` | distância do `pos` até a **próxima** linha horizontal |
| `side` | 0 = última cruzada foi vertical, 1 = horizontal |

### De onde vem `delta = |1/dir|`?

Se o raio tem direção `dir`, andar `delta.x` ao longo dele avança exatamente `1`
em x. Como o avanço em x por unidade de raio é `dir.x`, precisamos de
`delta.x = 1 / |dir.x|` unidades de raio pra ganhar 1 célula em x. (Semelhança de
triângulos — o raio é a hipotenusa, o cateto horizontal cresce `dir.x` por unidade.)

Nosso código ([dda.c](../src/render/dda.c)):

```c
d->delta.x = fabsf(1.0f / d->dir.x);
d->delta.y = fabsf(1.0f / d->dir.y);
```

> **Caso `dir.x == 0`** (raio perfeitamente vertical): `1/0 = inf`. Aí `side_dist.x`
> vira `inf` e o DDA nunca escolhe cruzar linha vertical — correto, porque um raio
> vertical de fato nunca cruza uma linha vertical. `cos` e `sin` nunca são 0 juntos.

### `step` e `side_dist` inicial

Dependem do sentido do raio. Se ele vai pra **esquerda** (`dir.x < 0`), a próxima
linha vertical é a **do lado esquerdo** da célula (a distância é a fração já
percorrida dentro da célula); se vai pra **direita**, é a do lado direito
(`1 - fração`):

```c
if (d->dir.x < 0)
{
    d->step_x = -1;
    d->side_dist.x = (d->pos.x - d->map_x) * d->delta.x;
}
else
{
    d->step_x = 1;
    d->side_dist.x = (d->map_x + 1 - d->pos.x) * d->delta.x;
}
```

`(pos.x - map_x)` é a fração dentro da célula (0 a 1). Multiplicando por `delta.x`
converte "fração de célula" em "distância ao longo do raio". Idem pra y.

---

## 5. O loop

Sempre avança pelo lado **mais próximo**, e marca qual foi:

```c
while (1)
{
    if (d->side_dist.x < d->side_dist.y)
    {
        d->side_dist.x += d->delta.x;   // agenda a PRÓXIMA linha vertical
        d->map_x += d->step_x;          // entra na célula vizinha em x
        d->side = 0;
    }
    else
    {
        d->side_dist.y += d->delta.y;
        d->map_y += d->step_y;
        d->side = 1;
    }
    if (touch(d->map_x * BLOCK, d->map_y * BLOCK, game))  // é parede?
        break ;
}
```

Note: `side_dist.x` sempre guarda a distância até a **próxima** linha vertical
ainda não cruzada. Quando cruzamos uma, somamos `delta.x` pra apontar pra seguinte.
Reaproveitamos o `touch()` (o mesmo da colisão) passando o canto da célula.

---

## 6. Extraindo os resultados

Quando o loop para, `map_x/map_y` é a célula da parede e `side` diz a face.

### 6.1 Distância perpendicular (sem fisheye!)

```c
if (d.side == 0)
    perp = d.side_dist.x - d.delta.x;
else
    perp = d.side_dist.y - d.delta.y;
```

Por que `- delta`? Porque no loop já somamos `delta` **antes** de checar a parede;
subtrair volta pra distância exata da face que batemos.

`perp` é a **distância perpendicular** à câmera (não a distância "reta" ao jogador).
Isso já corrige o **efeito olho-de-peixe** de graça — não precisa mais do
`fixed_dist` com `atan2/cos` que a gente usava. Multiplicamos por `BLOCK` pra
voltar a pixels: `ray.dist = perp * BLOCK`.

### 6.2 Onde bateu na parede (`wall_x`)

O ponto de impacto ao longo da face. Pra parede vertical, o que varia é `y`; pra
horizontal, `x`:

```c
if (d.side == 0)
    wall = d.pos.y + perp * d.dir.y;   // coordenada y do impacto (em células)
else
    wall = d.pos.x + perp * d.dir.x;
ray.wall_x = (wall - floorf(wall)) * BLOCK;   // só a parte fracionária → 0..BLOCK
```

`wall - floor(wall)` pega a posição **dentro** da célula (0 a 1), e `* BLOCK` põe em
pixels. Depois, no `draw_wall`, isso vira a coluna da textura:
`tex_x = wall_x / BLOCK * tex->width`.

### 6.3 Qual textura

`side` + sentido do raio ([textures.c](../src/render/textures.c) `pick_texture`):

```c
if (ray->side == 0)                 // parede vertical
    return (cos_a > 0 ? &tex.we : &tex.ea);
else                                // parede horizontal
    return (sin_a > 0 ? &tex.no : &tex.so);
```

> Se alguma face aparecer com a textura trocada, é só inverter os pares aqui
> (`we`↔`ea` / `no`↔`so`) — é convenção de eixos, não erro de algoritmo.

---

## 7. Desenhando a coluna ([draw.c](../src/render/draw.c) `draw_wall`)

Com `dist`, `wall_x` e a textura escolhida:

```c
height = (int)wall_height(ray.dist);      // altura projetada
start  = (HEIGHT - height) / 2;           // topo da parede (pode ser < 0)
tex_x  = (int)(ray.wall_x / BLOCK * tex->width);
y = start;
while (y < start + height)
{
    tex_y = (int)((float)(y - start) / height * tex->height);
    if (y >= 0 && y < HEIGHT)             // corta o que sai da tela
        put_pixel(column, y, tex_pixel(tex, tex_x, tex_y), game);
    y++;
}
```

`wall_height = (BLOCK / dist) * (WIDTH / 2)`: quanto mais longe (`dist` maior),
menor a parede. `tex_y` mapeia cada pixel vertical da coluna pra linha da textura,
proporcionalmente. O `if (y >= 0 && y < HEIGHT)` cuida de paredes maiores que a tela.

---

## 8. Fluxo completo (arquivos do projeto)

```
draw_loop (render.c)
 └─ cast_rays (render.c)         // 1 raio por coluna, ângulo varre o FOV (π/3)
     ├─ cast_ray (dda.c)         // init_dda → init_sides → run_dda → extrai perp/wall_x/side
     ├─ pick_texture (textures.c)// escolhe NO/SO/WE/EA
     └─ draw_wall (draw.c)       // amostra tex_pixel coluna a coluna
```

No **modo debug** (minimapa), em vez de `draw_wall` chamamos `draw_ray` pra desenhar
a linha do raio até `ray.hit` sobre o mapa 2D.

---

## 9. DDA vs ray-marcher — resumo

| | Ray-marcher (1px) | DDA |
|---|---|---|
| Passos até a parede | centenas | poucos (1 por linha da grade) |
| Precisão do impacto | ~1px de erro | exata |
| Detecção de face | ambígua em cantos | exata (`side`) |
| Fisheye | precisa corrigir à mão | perpendicular de graça |
| Costuras de textura | sim | não |

---

## 10. Pontos de atenção / para revisar

- **Unidades:** o DDA trabalha em células; só multiplicamos por `BLOCK` no fim.
- **`touch()` como teste de parede:** reaproveitado da colisão; retorna 1 também
  fora do mapa, o que naturalmente para o raio nas bordas.
- **`dir` com componente 0:** tratado via `inf` — vale testar olhando exatamente
  pros eixos (N/S/L/O puros) pra confirmar que não trava nem estoura.
- **Espelhamento de textura:** se algum lado ficar "invertido", inverte `wall_x`
  (`BLOCK - wall_x`) pra aquele `side`.
- **Referência clássica:** o tutorial do *Lode Vandevenne* ("Lodev raycasting") é a
  fonte canônica dessa formulação — vale ler pra fixar.
```

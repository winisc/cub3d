# Raycasting — Notas de Estudo

Este documento explica, de baixo pra cima, como um mapa 2D de caracteres
(`'1'` = parede, `'0'` = chão) vira uma cena 3D navegável. A técnica se chama
**raycasting** e foi a mesma usada no Wolfenstein 3D (1992).

A ideia em uma frase: **para cada coluna de pixels da tela, lançamos um raio a partir
do olho do jogador, medimos a que distância ele bate numa parede, e usamos essa
distância para decidir a altura da parede naquela coluna.** Perto = alto, longe =
baixo. O cérebro interpreta essa variação de altura como profundidade.

Os três pedaços do código trabalham juntos:

| Função | Papel |
|---|---|
| `draw_loop` | dispara um raio por coluna da tela, varrendo o campo de visão |
| `draw_line` | marcha **um** raio até encontrar uma parede |
| `touch`     | a cada passo do raio, responde "isso aqui é parede?" |

---

## 1. Fundamento: ângulos, radianos e o vetor de direção

Antes de tudo, é preciso entender como representamos "para onde o jogador olha".

### 1.1 Por que radianos e não graus?

As funções de `<math.h>` (`sin`, `cos`, `atan2`...) trabalham em **radianos**, não em
graus. A conversão é:

```
180° = PI radianos   →   1° = PI/180 rad
```

Tabela de referência mental:

| Graus | Radianos | No código |
|---|---|---|
| 360° | `2*PI`   | volta completa |
| 180° | `PI`     | meia volta |
| 90°  | `PI/2`   | um quarto (olhando "pra cima") |
| 60°  | `PI/3`   | o FOV inteiro |
| 30°  | `PI/6`   | metade do FOV |

Por isso `init_player` usa `player->angle = PI / 2` — começa olhando pra um eixo, não
"90 graus" literais.

### 1.2 Direção = um ponto no círculo unitário

Um **ângulo sozinho** não diz "ande tanto em x, tanto em y". Quem traduz ângulo em
movimento são o seno e o cosseno:

```
direção_x = cos(angle)
direção_y = sin(angle)
```

Esse par `(cos θ, sin θ)` é sempre um ponto em cima de um **círculo de raio 1** (o
*círculo unitário*). Consequência fundamental:

```
cos²(θ) + sin²(θ) = 1      (Teorema de Pitágoras no círculo)
```

Ou seja, o vetor `(cos θ, sin θ)` tem **comprimento exatamente 1**. Ele carrega só a
**direção**, sem "tamanho". Por isso, somar esse vetor à posição faz o raio (ou o
player) andar **1 unidade** naquela direção. Se quiser andar mais rápido, multiplica
por uma velocidade.

```
        sin(θ) ┤      . (cos θ, sin θ)   ← sempre a 1 de distância da origem
               │    /│
               │   / │ sin(θ)
               │  /θ │
       --------+-----+-------- cos(θ)
               │  cos(θ)
```

> **Atenção ao eixo Y:** na tela, `y` **cresce pra baixo** (linha 0 = topo). Então
> "ângulo subindo" no círculo matemático aponta pra baixo na tela. Isso normalmente
> não atrapalha porque tudo é consistente, mas é a causa nº 1 de confusão quando o
> movimento "parece invertido".

---

## 2. O campo de visão (FOV)

O jogador não enxerga 360° de uma vez — enxerga um **cone** à frente, como uma
lanterna. Esse cone é o **FOV (field of view)**. No código ele vale **60°**:

```c
PI / 3   // 60° → FOV total (abertura do cone)
PI / 6   // 30° → metade do FOV (do centro até cada borda)
```

**Por que 60°?** É o valor clássico que dá uma perspectiva "natural", parecida com a
visão humana central. FOV maior (ex: 90°) mostra mais dos lados, mas distorce mais nas
bordas (efeito "grande angular"). FOV menor parece um zoom/telescópio.

O cone vai de `angle - 30°` (borda esquerda) até `angle + 30°` (borda direita), com o
olhar `angle` exatamente no meio.

```
   borda esquerda          borda direita
   (angle - PI/6)          (angle + PI/6)
            \      |      /
             \     |     /
              \    |    /   ← FOV de 60°
               \   |   /
                \  |  /
                 \ | /
                  \|/
               [player] → angle (centro do cone)
```

---

## 3. O loop principal — um raio por coluna da tela

```c
fraction = PI / 3 / WIDTH;          // (1) passo angular entre raios consecutivos
start_x  = player->angle - PI / 6;  // (2) ângulo do PRIMEIRO raio (borda esquerda)
i = 0;
while (i < WIDTH)                    // (3) um raio para cada coluna de pixels
{
    draw_line(player, game, start_x);
    start_x += fraction;            // (4) gira um tiquinho pro próximo raio
    i++;
}
```

### 3.1 A correspondência raio ↔ coluna

A tela tem `WIDTH` colunas de pixels (ex: 1280). Distribuímos o FOV de 60° igualmente
entre essas colunas: **cada coluna recebe exatamente um raio**.

```c
fraction = (PI / 3) / WIDTH;   // 60° dividido por 1280 colunas
```

Com WIDTH = 1280, isso dá `≈ 0.047°` por raio — um leque finíssimo. O raio nº 0 desenha
a coluna 0 (extrema esquerda da tela), o raio nº 1279 desenha a coluna 1279 (extrema
direita).

### 3.2 Por que começar em `angle - PI/6`?

Como queremos varrer da **esquerda pra direita** (acompanhando as colunas, que vão de
0 à esquerda até WIDTH-1 à direita), o **primeiro** raio é o mais à esquerda:
`angle - 30°`. A cada iteração somamos `fraction`, girando o raio pra direita, até
chegar em `angle + 30°` no último.

### 3.3 Exemplo numérico

Suponha `player->angle = 90°` (`PI/2`) e WIDTH = 1280:

| `i` | ângulo do raio | onde aponta |
|---|---|---|
| 0    | 60°  (`90 - 30`)        | borda esquerda do FOV |
| 640  | ~90° (centro)          | exatamente pra frente |
| 1279 | ~120° (`90 + 30`)      | borda direita do FOV |

Cada um desses raios será "marchado" pela `draw_line`.

---

## 4. `draw_line` — marchando UM raio até a parede

```c
void	draw_line(t_player *player, t_game *game, float start_x)  // start_x = ângulo do raio
{
    ray_x = player->pos.x;        // (a) o raio nasce na posição do player
    ray_y = player->pos.y;
    cos_angle = cos(start_x);     // (b) decompõe o ângulo em vetor de direção
    sin_angle = sin(start_x);
    while (!touch(ray_x, ray_y, game))            // (c) anda enquanto NÃO bater
    {
        put_pixel(ray_x, ray_y, 0xFF0000, game);  // (d) marca o caminho (vermelho)
        ray_x += cos_angle;       // (e) dá um passo na direção do raio
        ray_y += sin_angle;
    }
}
```

### 4.1 A mecânica do "ray marching"

A estratégia é a mais intuitiva possível: **dar passinhos pequenos na direção do raio
até esbarrar numa parede**. Como um cego andando com a mão estendida.

- **(a)** O raio parte exatamente de onde o player está.
- **(b)** `cos(ângulo)` e `sin(ângulo)` viram o vetor de direção unitário (seção 1.2).
  Como o comprimento é 1, **cada passo avança ~1 pixel** — granularidade fina.
- **(c)** O laço roda *enquanto* `touch` retornar 0 (chão). No momento em que `touch`
  retorna 1 (parede), o laço para — e `ray_x`/`ray_y` ficam guardando **o ponto exato
  da colisão**. Esse ponto é o que vamos medir depois.
- **(d)** Pinta um pixel vermelho na posição atual. É isso que, no modo 2D, desenha a
  "linha" do raio saindo do player.
- **(e)** Soma o vetor de direção à posição → o raio avança um passo. Volta pro teste.

### 4.2 Visualizando um passo

Se `start_x` (ângulo) = 0° (raio apontando pra direita pura):
- `cos(0°) = 1`, `sin(0°) = 0`
- cada passo: `ray_x += 1`, `ray_y += 0` → anda só na horizontal. ✅

Se o ângulo = 45°:
- `cos(45°) ≈ 0.707`, `sin(45°) ≈ 0.707`
- cada passo: anda `0.707` em x **e** `0.707` em y. A diagonal de um passo desses tem
  comprimento `√(0.707² + 0.707²) = 1`. Ainda **1 pixel por passo** — é o que mantém a
  medida de distância consistente em qualquer direção.

### 4.3 Limitação deste método

Passo fixo de 1 pixel é simples mas tem dois custos:
1. **Performance:** numa sala grande, um raio pode dar centenas de passos. Multiplica
   por WIDTH raios por frame → muitas iterações.
2. **Precisão:** o ponto de colisão fica ~1 pixel impreciso (paramos *logo depois* de
   entrar na parede, não na borda exata).

A alternativa profissional é o **DDA** (Digital Differential Analyzer), que pula
direto de uma fronteira de célula pra próxima, em vez de passos fixos — bem mais
rápido e exato. Pro minimapa/protótipo, o passo fixo é suficiente.

---

## 5. `touch` — convertendo pixel em célula do grid

```c
int	touch(float px, float py, t_game *game)
{
    x = px / BLOCK;                  // pixel → índice de coluna do grid
    y = py / BLOCK;                  // pixel → índice de linha do grid
    if (game->map[y][x] == '1')      // essa célula é parede?
        return (1);
    return (0);
}
```

### 5.1 Dois sistemas de coordenadas

Há **duas réguas diferentes** no jogo:

| Sistema | Unidade | Exemplo |
|---|---|---|
| **Pixel** (mundo) | pixels contínuos | o player está em `(640.0, 360.0)` |
| **Grid** (mapa) | índices de célula inteiros | `map[5][9]` |

Cada célula do mapa ocupa `BLOCK × BLOCK` pixels (BLOCK = 64). A conversão é uma
**divisão inteira**:

```c
x = px / BLOCK;   // ex: pixel 200 → célula 200/64 = 3
y = py / BLOCK;
```

Tudo entre o pixel 192 e 255 cai na célula 3 (porque `192/64 = 3` e `255/64 = 3`). A
divisão "joga fora" a posição dentro da célula, deixando só *qual* célula.

### 5.2 Por que `map[y][x]` e não `map[x][y]`

O mapa é um array de strings. A **primeira** dimensão escolhe a *string* (a linha =
eixo vertical = **y**), a **segunda** escolhe o *caractere* dentro dela (a coluna =
eixo horizontal = **x**). Inverter pra `map[x][y]` lê a célula errada (e pode estourar
o array se as dimensões forem diferentes).

### 5.3 O perigo escondido: acesso fora dos limites

`touch` **não verifica** se `x` e `y` estão dentro do mapa. Se um raio escapar do mapa
sem nunca achar `'1'`, `map[y][x]` lê memória inválida → **segfault**. Hoje isso não
acontece porque o mapa de teste é **cercado de paredes** (`'1'` em toda a borda), então
todo raio bate antes de sair. Mas com um mapa "aberto" o programa quebraria. Numa
versão robusta, `touch` deveria checar os limites antes do acesso.

---

## 6. Juntando tudo no modo 2D (debug)

```
draw_loop:  para cada coluna i (0 .. WIDTH-1)
   └─ calcula o ângulo do raio (start_x, varrendo o FOV da esquerda à direita)
       └─ draw_line: marcha o raio pixel a pixel naquele ângulo
           └─ touch: a cada passo pergunta "já bati numa parede?"
                ├─ não  → pinta vermelho e dá mais um passo
                └─ sim  → para; guarda o ponto de colisão em ray_x/ray_y
```

No modo 2D (com `player->debug` ligado), o resultado é o leque de raios vermelhos
saindo do player e parando nas paredes azuis do minimapa. É a forma de **ver** o
raycasting funcionando antes de projetar em 3D.

---

## 7. Projeção 3D — de distância para altura de parede

Quando `player->debug` está **desligado**, em vez de desenhar o raio no chão,
desenhamos uma **fatia vertical de parede** na coluna `i` da tela:

```c
float dist   = fixed_dist(player->pos.x, player->pos.y, ray_x, ray_y, game);
float height = (BLOCK / dist) * (WIDTH / 2);   // (1) altura projetada da parede
int start_y  = (HEIGHT - height) / 2;          // (2) coordenada Y do topo da fatia
int end      = start_y + height;               // (3) coordenada Y da base da fatia
while (start_y < end)                          // (4) desenha a coluna vertical
{
    put_pixel(i, start_y, 255, game);          //     i = coluna; 255 = azul
    start_y++;
}
```

### 7.1 A intuição: perspectiva é "altura ÷ distância"

Estique o braço e levante o polegar. Perto do rosto ele tampa meia parede; esticado,
tampa um tijolo. O **mesmo objeto** parece menor quanto mais longe. Matematicamente, a
altura aparente é **inversamente proporcional à distância**:

```
altura_na_tela = altura_real × (distância_do_plano_de_projeção / distância_do_objeto)
```

No nosso código:

```c
height = (BLOCK / dist) * (WIDTH / 2);
//         ▲    ▲           ▲
//         │    │           └─ distância do "plano de projeção" (constante)
//         │    └─ distância do player até a parede (varia por raio)
//         └─ altura real da parede (1 bloco = 64)
```

- `BLOCK` é a altura "real" da parede no mundo.
- Dividir por `dist` cria a perspectiva: **dobrou a distância → metade da altura**.
- `(WIDTH / 2)` é a **constante de projeção**. Ela representa a distância do olho até a
  tela virtual (o "plano de projeção"). É uma escala: maior = paredes maiores na tela.

### 7.2 De onde vem `WIDTH / 2`

A distância do plano de projeção, em teoria, é:

```
dist_plano = (WIDTH / 2) / tan(FOV / 2)
```

Com FOV = 60°, `tan(30°) ≈ 0.577`, então o valor "correto" seria
`(WIDTH/2) / 0.577 ≈ WIDTH × 0.866`. O código usa só `WIDTH/2`, ou seja, uma
**aproximação** que ignora o `tan`. O efeito prático é que as paredes ficam um pouco
mais "achatadas" do que o geometricamente exato — mas continua parecendo 3D. É um
ajuste de gosto/simplicidade; dá pra refinar depois.

### 7.3 Centralizando a fatia na tela

```c
start_y = (HEIGHT - height) / 2;
end     = start_y + height;
```

A parede é desenhada **centralizada verticalmente**. A sobra (`HEIGHT - height`) é
dividida igualmente: metade vira espaço **acima** (futuro teto), metade **abaixo**
(futuro chão). O meio da parede cai sempre na **linha do horizonte** (`HEIGHT / 2`).

```
   y=0       ┌───────────────┐  ← topo da tela
             │     (teto)     │  ← (HEIGHT - height)/2 pixels vazios
   start_y → ├───────────────┤  ← topo da parede
             │░░░░░░░░░░░░░░░│
             │░░░ PAREDE ░░░░│  ← height pixels (a fatia desenhada)
             │░░░░░░░░░░░░░░░│
   end →     ├───────────────┤  ← base da parede
             │     (chão)     │  ← mesma quantidade de pixels vazios
HEIGHT-1     └───────────────┘  ← base da tela
```

### 7.4 O laço que desenha a coluna

```c
while (start_y < end)
{
    put_pixel(i, start_y, 255, game);   // SEMPRE na coluna i; desce em y
    start_y++;
}
```

Repare: `x` é **fixo** em `i` (a coluna desta iteração do `draw_loop`), e só o `y`
varia, de `start_y` até `end`. Isso desenha **uma linha vertical** — a fatia da
parede. `255` em hexadecimal é `0x0000FF` = **azul puro**.

### 7.5 Por que o conjunto vira 3D

Cada raio do FOV vira **uma coluna** na tela. Paredes **próximas** → `dist` pequeno →
`height` grande → coluna **alta**. Paredes **longe** → `dist` grande → coluna
**baixa**. Colocando as `WIDTH` colunas lado a lado, o olho lê a variação de alturas
como **profundidade**:

```
parede:    perto         meio          longe
           ┌────┐
           │░░░░│         ┌────┐
coluna  →  │░░░░│         │░░░░│        ┌────┐
na tela    │░░░░│         │░░░░│        │░░░░│
           │░░░░│         └────┘        └────┘
           └────┘
          (height        (height        (height
           grande)        médio)         pequeno)
```

---

## 8. `fixed_dist` — a distância corrigida (anti-fisheye)

```c
float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x  = x2 - x1;
    float delta_y  = y2 - y1;
    float angle    = atan2(delta_y, delta_x) - game->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return (fix_dist);
}
```

### 8.1 O problema do "olho de peixe" (fisheye)

Se usássemos a distância **crua** (linha reta do player até a parede), as paredes
apareceriam **curvadas/infladas** — maiores no centro da tela e abauladas nas bordas.

Por quê? Imagine olhar pra uma parede **plana** bem à sua frente. O raio central bate
de frente (curto). Os raios das bordas batem na mesma parede, mas **na diagonal**,
percorrendo um caminho **mais longo** — só por causa do ângulo, não porque a parede
está mais longe. Distância maior → altura menor → a parede plana parece *afundar* nas
bordas. Isso é o fisheye.

```
              parede plana
   ════════════════════════════════
      \         |         /
       \ longo  |curto   / longo
        \       |       /
         \      |      /
          \     |     /
           \    |    /
            [player]
```

### 8.2 A correção: projetar na direção do olhar

A solução é não usar a distância "em linha reta", e sim a **componente da distância na
direção pra onde o player olha** (a distância perpendicular ao plano de projeção).
Isso se faz com cosseno:

1. `atan2(delta_y, delta_x)` → o ângulo **real** do raio que bateu.
2. `- game->player.angle` → quanto esse raio se desvia do centro do olhar (`angle`).
   Para o raio central, isso é ~0; para os das bordas, ~±30°.
3. `distance(...) * cos(angle)` → encurta a distância dos raios laterais exatamente na
   medida certa. Para o raio central, `cos(0) = 1` (não muda). Para um raio a 30°,
   `cos(30°) ≈ 0.866` (encurta 13%, compensando o caminho diagonal mais longo).

Resultado: a parede plana volta a ter **altura uniforme** na tela. Reto.

### 8.3 `distance` — Pitágoras puro

```c
float	distance(float x, float y)
{
    return (sqrt(x * x + y * y));   // comprimento do vetor (delta_x, delta_y)
}
```

É só o teorema de Pitágoras: o comprimento da hipotenusa formada pelos catetos
`delta_x` e `delta_y`. Dá a distância em linha reta entre dois pontos.

---

## 9. ⚠️ Pontos de atenção (resumo)

1. **Nome `start_x`** → na verdade é um **ângulo**, não uma coordenada. Renomear pra
   `ray_angle` evita muita confusão de leitura.
2. **Fisheye** → a correção (`* cos`) já está em `fixed_dist`. Se as paredes curvarem,
   é aqui que se olha.
3. **Passo de 1 pixel** no `draw_line` → simples, mas lento e pode "furar" paredes
   finas. Trocar por **DDA** quando quiser performance/precisão.
4. **`touch` sem checar limites** → mapa não-fechado = segfault. Adicionar verificação
   de bordas antes de `map[y][x]`.
5. **`dist` perto de 0** → se o player encostar na parede, `BLOCK / dist` explode
   (altura gigante). Vale um piso mínimo na distância (ex: `if (dist < 0.1) dist = 0.1`).
6. **Eixo Y pra baixo** → lembrar que na tela `y` cresce pra baixo; afeta a intuição de
   "subir/descer" e o sinal dos ângulos.

---

## 10. Próximos passos

- **Teto e chão:** preencher de cor o espaço **acima de `start_y`** e **abaixo de
  `end`** (hoje fica preto).
- **Texturas:** em vez de azul sólido, mapear cada pixel da fatia pra um pixel de uma
  imagem de parede (precisa saber *onde* na parede o raio bateu e *qual* parede).
- **DDA:** trocar o ray marching de passo fixo pelo algoritmo de grid, mais rápido e
  exato.
- **Cores por lado (NO/SO/WE/EA):** escolher a textura conforme a face da parede que o
  raio atingiu.

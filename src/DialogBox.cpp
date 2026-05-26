#include "raylib.h"
#include <string>
#include <vector>
#include "RenderComponent.h"

// Calcula la posición X acumulada de cada carácter en una línea de texto
static std::vector<float> BuildCharPositions(Font font, const std::string& line,
   float startX, float fontSize)
{
   std::vector<float> positions;
   float x = startX;
   for (char c : line) {
       char buf[2] = { c, '\0' };
       x += MeasureTextEx(font, buf, fontSize, 2.0f).x + 2.0f;
       positions.push_back(x);
   }
   return positions;
}

class DialogBox : public RenderComponent {
   enum State { BORDER, TEXT };

   Rectangle   rect;
   Font        font;
   float       fontSize = 30.0f; //TAMAÑO DE LA FUENTA
   float       padding = 30.0f;
   float       textSpeed = 1000.0f; //RAPIDEZA ANIMACION RELLENO
   float       borderSpeed = 1500.0f; //RAPIDEZA ANIMACION BORDES

   float borderProgress = 0.0f;
   float totalPerimeter = 0.0f;
   float animX = 10.0f;

   std::vector<std::string>         lines;        // pares: línea de texto + línea de retorno vacía
   std::vector<std::vector<float>>  charPositions;
   size_t currentLine = 0;
   State  state = BORDER;
   bool   done = false;

   static constexpr float BORDER_T = 30.0f;

   float TextLineH()   const { return fontSize + 9.0f; }
   float ReturnLineH() const { return fontSize * 1.00f; }

public:
   DialogBox(Rectangle pos, const std::vector<std::string>& dialogue, Font f)
       : rect(pos), font(f)
   {
       // Intercalar líneas reales con líneas de retorno vacías
       for (size_t i = 0; i < dialogue.size(); ++i) {
           lines.push_back(dialogue[i]);
           if (i + 1 < dialogue.size()) lines.push_back("");
       }

       // Pre-calcular posiciones de caracteres para cada línea de texto
       charPositions.resize(lines.size());
       for (size_t i = 0; i < lines.size(); i += 2)
           charPositions[i] = BuildCharPositions(font, lines[i], rect.x + padding, fontSize);

       totalPerimeter = (rect.width + rect.height) * 2.0f;
       animX = rect.x + padding;
   }

   void draw(float dt) override {
       DrawBorder();
       if (state != BORDER) {
           DrawContent();
       }

       if (done) return;

       if (state == BORDER) {
           borderProgress += borderSpeed * dt;
           if (borderProgress >= totalPerimeter) {
               borderProgress = totalPerimeter;
               state = TEXT;
           }
           return;
       }

       // state == TEXT
       const float startX = rect.x + padding;
       const float endX = rect.x + rect.width - padding;
       const bool  isText = (currentLine % 2 == 0);
       const float target = isText ? endX : startX;
       const float dir = isText ? 1.0f : -1.0f;

       animX += dir * textSpeed * dt;
       if ((isText && animX >= target) || (!isText && animX <= target)) {
           animX = target;
           if (currentLine + 1 < lines.size()) {
               ++currentLine;
               animX = isText ? endX : startX;  // posición de inicio del siguiente segmento
           }
           else {
               done = true;
           }
       }
   }

   bool IsDone() const { return done; }

private:
   void DrawBorder() const {
       // Dibuja el borde como un "lápiz" que recorre el perímetro en orden
       struct Side { float x, y, w, h; float length; };
       Side sides[4] = {
           { rect.x,                            rect.y,                             rect.width,  BORDER_T,  rect.width  },
           { rect.x + rect.width - BORDER_T,    rect.y,                             BORDER_T,    rect.height, rect.height },
           { rect.x,                            rect.y + rect.height - BORDER_T,    rect.width,  BORDER_T,  rect.width  },
           { rect.x,                            rect.y,                             BORDER_T,    rect.height, rect.height },
       };
       // Correcciones para que el borde izquierdo y derecho no se superpongan
       sides[1].y = rect.y;
       sides[2].x = rect.x + rect.width - sides[2].w;   // empieza por la derecha
       sides[3].y = rect.y + rect.height - BORDER_T;    // empieza por abajo

       float remaining = borderProgress;
       // Arriba: izq->der
       float d = (remaining > rect.width) ? rect.width : remaining;
       if (d > 0) DrawRectangle(rect.x, rect.y, d, BORDER_T, BLACK);
       remaining -= rect.width;
       // Derecha: arriba->abajo
       d = (remaining > rect.height) ? rect.height : remaining;
       if (remaining > 0 && d > 0)
           DrawRectangle(rect.x + rect.width - BORDER_T, rect.y, BORDER_T, d, BLACK);
       remaining -= rect.height;
       // Abajo: der->izq
       d = (remaining > rect.width) ? rect.width : remaining;
       if (remaining > 0 && d > 0)
           DrawRectangle(rect.x + rect.width - d, rect.y + rect.height - BORDER_T, d, BORDER_T, BLACK);
       remaining -= rect.width;
       // Izquierda: abajo->arriba
       d = (remaining > rect.height) ? rect.height : remaining;
       if (remaining > 0 && d > 0)
           DrawRectangle(rect.x, rect.y + rect.height - d, BORDER_T, d, BLACK);
   }

   void DrawContent() const {
       if (done)
           DrawRectangle(rect.x + BORDER_T, rect.y + BORDER_T,
               rect.width - BORDER_T * 2, rect.height - BORDER_T * 2, BLACK);

       const float startX = rect.x + padding;
       const float endX = rect.x + rect.width - padding;
       const float totalW = endX - startX;
       float y = rect.y + padding;

       for (size_t i = 0; i <= currentLine && i < lines.size(); ++i) {
           const bool isText = (i % 2 == 0);
           const float lineH = isText ? TextLineH() : ReturnLineH();
           const bool  isCurrent = (i == currentLine);

           if (!isCurrent) {
               // Línea ya completada
               DrawRectangle(startX, y, totalW, lineH, BLACK);
               if (isText)
                   DrawTextEx(font, lines[i].c_str(), { startX, y }, fontSize, 2.0f, WHITE);
           }
           else {
               // Línea en animación
               if (isText) {
                   float fillW = animX - startX;
                   DrawRectangle(startX, y, fillW, lineH, BLACK);
                   float drawX = startX;
                   for (size_t j = 0; j < lines[i].size(); ++j) {
                       if (animX >= charPositions[i][j]) {
                           char buf[2] = { lines[i][j], '\0' };
                           DrawTextEx(font, buf, { drawX, y }, fontSize, 2.0f, WHITE);
                       }
                       char buf[2] = { lines[i][j], '\0' };
                       drawX += MeasureTextEx(font, buf, fontSize, 2.0f).x + 2.0f;
                   }
               }
               else {
                   float fillW = endX - animX;
                   DrawRectangle(animX, y, fillW, lineH, BLACK);
               }
           }
           y += lineH;
       }
   }
};

/**int main() {
   InitWindow(1920, 900, "Alex Kidd");

   Font font = LoadFont("resources/alex-kidd-in-miracle-world-sms.otf");

   DialogBox dialog(
       { 1920 / 2 - 500, 180, 840, 160 },
       { "Welcome! Please buy", "the things that you like." },
       font
   );


   DialogBox dialogThanks(
       { 1920 / 2 - 500, 180, 350, 85 },
       { "Thank you." },
       font
   );

   SetTargetFPS(60);
   while (!WindowShouldClose()) {
       dialog.Update(GetFrameTime());
       BeginDrawing();
       ClearBackground(RED);
       dialog.Draw();
       EndDrawing();
   }

   CloseWindow();
   return 0;
   }*/

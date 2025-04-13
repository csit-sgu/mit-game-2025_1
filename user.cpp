#include "user.hpp"
#include "internal.hpp"

#include <raymath.h>
#include <raylib.h>

// Задание CheckCollision.
//
// Эта функция выполняет проверку на столкновение двух объектов (obj1 и obj2).
//
// Функция сначала вычисляет разницу между позициями obj2 и obj1 и сохраняет ее
// в вектор d. Далее можно составить вектор q, который для каждой из осей
// посчитает разность расстояния объектов и полусуммы размерностей объектов
// (поля width и height).
//
// Если обе компоненты q отрицательны, это означает, что коллайдеры
// пересекаются, и функция возвращает true, а также вектор q, который содержит
// разницу по каждой координате между краем коллайдера obj1 и коллайдера obj2.
// Если хотя бы одна компонента q положительна, значит, коллайдеры не
// пересекаются, и функция возвращает false, а также вектор {0, 0}.
//
// Возможное решение может занимать примерно 15-18 строк.
// Ваше решение может сильно отличаться.
//
Collision CheckCollision(Object &obj1, Object &obj2) {
    return Collision{};
}

// Задание SolveCollision.
//
// Наше решение коллизий не является идеальным, но будем считать его достаточно
// хорошим для нашей игры. При желании можно превзойти эту реализацию.
//
// Если коллизия не произошла (c.exists равно false), то ничего делать не нужно.
// Если коллизия по горизонтали (std::abs(c.overlap.x)) больше, чем по
// вертикали (std::abs(c.overlap.y)), то объект obj перемещается на величину
// c.overlap.x влево или вправо в зависимости от направления коллизии. В
// противном случае, объект перемещается на величину c.overlap.y вверх или вниз
// в зависимости от направления коллизии. Если перекрытие по вертикали
// отрицательное (c.overlap.y < 0), то у объекта obj обнуляются ускорение и
// скорость по оси y, а также устанавливается возможность прыгать
// (obj.physics.can_jump = true), если скорость по оси y была меньше 0. Если
// коллизия по вертикали положительна (c.overlap.y > 0), то скорость объекта
// по оси y обнуляется (obj.physics.speed.y = 0).
//
// Возможное решение может занимать примерно 14-20 строк.
// Ваше решение может сильно отличаться.
//
void SolveCollision(Object &obj, Collision c, float dt) {}

// Задание FixCollisions.
//
// Эта функция находит и решает все коллизии нашего игрового мира. Делает она
// это, попарно перебирая все объекты.
//
// Сначала пройдёмся в цикле по всем объектам сцены (scene). Это можно очень
// удобно сделать сделать с помощью цикла for-each, который появился в С++11:
// for (Object &obj1 : scene). Для каждого объекта проверим, что он подчиняется
// физическим законам нашего игрового мира. Для этого у него должен быть
// коллайдер (obj1.collider.enabled) - это некий прямоугольник, описывающий
// физические границы объекта. Кроме того, этот коллайдер должен быть
// динамическим (ColliderType::DYNAMIC), то есть объект может двигаться сам или
// под воздействием внешних сил, это можно проверить, используя метод of_type
// для obj.collider.
//
// Если наш объект удовлетворяет условиям, описанным выше, точно так же
// переберём все объекты сцены в качестве второго объекта, коллизию с которым и
// будем проверять. Убедимся в следующих вещах:
// - obj1 != obj2. Объект не может столкнуться сам с собой.
// - У obj2 включён компонент коллайдер.
// - У коллайдера obj2 тип DYNAMIC или STATIC.
//
// И вот теперь, мы точно можем быть уверены, что obj1 и obj2 могут устроить
// коллизию, которую нужно будет устранить. Для этого воспользуемся функцией
// CheckCollision, которая вернёт коллизию, и останется только вызвать
// SolveCollision, которая решит коллизию.
//
// Рекомендуемые функции для выполнения задания:
// - CheckCollision
// - SolveCollision
//
// Возможное решение может занимать примерно 14-20 строк.
// Ваше решение может сильно отличаться.
//
void FixCollisions(Scene &scene, float dt) {}

// Задание ApplyGravity.
//
// Эта функция должна применять эффект гравитации к конкретному объекту (obj).
// Сначала нужно проверить, что полученный объект поклоняется физическим законам
// нашего игрового мира. Для этого нужно, чтобы у него был включен компонент
// физики (obj.physics.enabled) и коллайдер должен быть типа
// ColliderType::DYNAMIC. Последнее можно проверить, используя метод of_type для
// obj.collider.
//
// Для того, чтобы физика повлияла на объект нужно сделать несколько вещей:
// 1. Изменить ускорение (acceleration) в компоненте obj.physics, прибавив к
//    нему ускорение свободного падения на время в квадрате. В нашем случае
//    ускорение свободного падения - это вектор направленный вниз с длинной
//    GRAVITY, а время с прошлого кадра хранится в переменной dt.
// 2. Увеличить скорость на новое значение ускорения.
// 3. Ограничить скорость, чтобы она не превышала максимальную скорость падения.
//    То есть в какой-то момент падения, игрок перестаёт ускоряться.
//    Здесь можно поиграться со значениями. Нам, например, понравилось 200 в
//    качестве максимальной скорости падения.
// 4. Осталось только изменить позицию игрока, прибавив к ней скорость,
//    умноженную на время с прошлого кадра.
//
// Возможное решение может занимать примерно 8-9 строки.
// Ваше решение может сильно отличаться.
//
void ApplyGravity(Object &obj, float dt) {}

// Задание MakeJump.
//
// Эта функция вызывается при нажатии на кнопку прыжка (пробел). Необходимо
// проверить, что в данный момент игрок может совершить прыжок
// (obj.physics.can_jump). В таком случае нужно придать ему скорость вертикально
// вверх. С конкретными значениями можно поиграться, но желательно, чтобы прыжок
// выглядел достаточно реалистично. И после придания скорости остаётся изменить
// флаг, отвечающий за возможность прыжка. Мы считаем, что игрок не может
// прыгать, пока он не находится на земле. Приземление в этой функции
// рассматривать не нужно.
// dt можно не использовать.
//
// Возможное решение может занимать примерно 3 строки.
// Ваше решение может сильно отличаться.
//
void MakeJump(Object &obj, float dt) {}

// Задание MoveCameraTowards.
//
// Эта функция вызывается каждый кадр игры. Необходимо, чтобы камера следовала
// за объектом obj с некоторым запозданием. Для этого нужно вычислить вектор,
// по которому движется камера с помощью полей obj.position и ctx.camera_pos и
// сделать так, чтобы поле ctx.camera_pos передвигалась с некоторой скоростью
// вдоль этого вектора. Так как скорость указывается в метрах в секунду, а
// функция вызывается чаще, чем раз в секунду, необходимо изменять позицию
// камеры только на то расстояние, которое она могла пройти после предыдущего
// вызова функции. Время прошедшее с прошлого вызова передаётся в параметре dt
//
// Рекомендуемые функции для выполнения задания:
// - Vector2Length
//
// Возможное решение может занимать примерно 5 строк.
// Ваше решение может сильно отличаться.
//
void MoveCameraTowards(Context &ctx, Object &obj, float dt) {}

// Задание CheckPlayerDeath.
//
// Эта функция вызывается каждый кадр игры. Для её реализации необходимо
// проходить по всем объектам в сцене, у которых включён obj.enemy.enabled.
// После этого, функция должна вернуть true в случае, если объект player
// прикоснулся к такому объекту obj. Иначе, функция возвращает false.
//
// Рекомендуемые функции для выполнения задания:
// - CheckCollision
//
// Возможное решение может занимать примерно 6-7 строк.
// Ваше решение может сильно отличаться.
//
bool CheckPlayerDeath(Object &player, Scene &scene) {
    return false;
}

// Задание CheckFinish.
//
// Эта функция вызывается каждый кадр игры. Для её реализации необходимо
// проходить по всем объектам в сцене, у которых включён obj.finish.enabled.
// После этого, функция должна вернуть true в случае, если объект player
// прикоснулся к такому объекту obj. Иначе, функция возвращает false.
//
// Рекомендуемые функции для выполнения задания:
// - CheckCollision
//
// При выполнении этого задания у вас есть возможность добавить свою текстуру
// финиша уровня Assets/finish.png
//
// Возможное решение может занимать примерно 6-7 строк.
// Ваше решение может сильно отличаться.
//
bool CheckFinish(Object &player, Scene &scene) {
    return false;
}

// Задание EnemyAI.
//
// Данная функция реализует искусственный интеллект для врагов в игровой сцене.
//
// Реализация достаточно свободная. Мы предлагаем следующее: противник будет
// преследовать игрока.
//
// Внутри функции определяется объект игрока путем вызова функции find_player,
// которая возвращает указатель на объект игрока в сцене.
//
// Затем функция должна вычислить разницу между позицией противника и позицией
// игрока, чтобы понять, в каком направлении нужно двигаться. Значение
// перемещения move вычисляется, умножая скорость движения врага на время,
// прошедшее с последнего кадра.
//
// Затем функция изменяет позицию врага, добавляя или вычитая значение move из
// его текущей позиции в зависимости от того, находится ли противник слева или
// справа от игрока.
//
// Рекомендуемые функции для выполнения задания:
// - find_player
//
// При выполнении этого задания у вас есть возможность добавить свою текстуру
// противника Assets/enemy1.png
//
// Возможное решение может занимать примерно 16-20 строк.
// Ваше решение может сильно отличаться.
//
void EnemyAI(Object &enemy, Scene &scene, float dt) {
    Object *player = find_player(scene);

    if (!player) {
        return;
    }

    float dx = enemy.position.x - player->position.x;
    float move = enemy.enemy.speed * dt;

    dx > 0 ? enemy.position.x -= move : enemy.position.x += move;
}

// Задание PlayerControl.
//
// Эта функция отвечает за управление игроком. Если ввод не заблокирован
// (ctx.input_blocked), то функция обрабатывает ввод с клавиатуры и меняет
// положение игрока на основе нажатых клавиш.
//
// - Если клавиша KEY_SPACE нажата, то вызывается функция MakeJump, которая
//   заставляет игрока совершить прыжок.
// - Если клавиша KEY_J нажата, то вызывается функция ShootBullet, которая
//   выпускает снаряд.
// - Если клавиша KEY_A нажата, то игрок начинает движение влево, если KEY_D -
//   вправо.
// - Движение игрока определим 2D-вектором move, где каждая компонента принимает
//   значение из множества {-1, 0, 1}. Например, вектор {-1, 0} — будет
//   описывать движение влево. Тогда положение игрока меняется на основе вектора
//   move, умноженного на скорость игрока и время, прошедшее с прошлого кадра.
//
// Рекомендуемые функции для выполнения задания:
// - IsKeyDown
// - MakeJump
// - ShootBullet
//
// При реализации данного задания у вас есть возможность добавить свою
// текстуру игрока Assets/player.png.
//
// Возможное решение может занимать примерно 16-20 строк.
// Ваше решение может сильно отличаться.
//
void PlayerControl(Context &ctx, Object &player, float dt) {}

// Задание ShootBullet.
//
// Данная функция вызывается при нажатии игроком на кнопку выстрела. Необходимо
// создать новый объект bullet = Object() и установить у него некоторые
// из полей. Так как снаряды запускает игрок, то начальная позиция пули
// bullet.position должна совпадать с позицией игрока. Картинка пули должна
// считываться из файла Assets/bullet.png. Для добавления её к объекту
// необходимо сконструировать новый объект Render и присвоить его полю
// bullet.render. Для создания физического тела пули необходимо сконструировать
// объект Collider и присвоить его полю bullet.collider. Для автоматического
// определения размеров тела по графике, конструктору нужно передать
// bullet.render. Чтобы игрок не сталкивался с пулей конструктору также нужно
// передать тип физического тела - ColliderType::EVENT.
//
// Далее необходимо указать параметры самой пули. Для этого можно использовать
// конструктор класса Bullet, в котором указать скорость пули и длительность
// её жизни. Так как пуля должна выпускаться в том же направлении, в
// которое смотрит игрок, скорость по оси x будет отрицательной, если
// player.player.direction равна Direction::LEFT, и положительной, если равна
// Direction::RIGHT. Время жизни пули необходимо указывать для того, чтобы
// она уничтожилась в функции UpdateBullet через указанное количество секунд,
// а не летела вечно.
//
// Сконструированный объект Bullet необходимо записать в поле bullet.bullet.
// Далее, добавить этот объект в сцену можно с помощью функции Spawn.
//
// Рекомендуемые функции для выполнения задания:
// - Конструктор класса Render
// - Конструктор класса Collider
// - Конструктор класса Bullet
// - Spawn
//
// При реализации данного задания у вас есть возможность добавить свою
// текстуру пули Assets/bullet.png.
//
// Возможное решение может занимать примерно 8-10 строк.
//
void ShootBullet(Context &ctx, Object &player, float dt) {}

// Задание UpdateBullet.
//
// Эта функция вызывается для всех снарядов, запущенных игроком. У
// объекта пули есть параметры obj.bullet.speed, obj.bullet.lifetime и
// obj.bullet.max_lifetime. Первый необходимо использовать для перемещения
// снаряда по уровню. Сделать это можно прибавляя скорость к позиции
// obj.position объекта. Так как скорость пули указывается в метрах в секунду,
// а функция вызывается чаще, чем раз в секунду, необходимо изменять позицию
// пули только на то расстояние, которое она могла пролететь после предыдущего
// вызова функции. Время прошедшее с прошлого вызова передаётся в параметре dt.
//
// Второй и третий параметры необходимо использовать для уничтожения пули через
// некоторое время после её запуска. Параметр obj.bullet.lifetime должен хранить
// время, прошедшее с запуска пули. Для этого при каждом вызове этой функции
// он должен изменяться на время, прошедшее с прошлого вызова. Как только
// obj.bullet.lifetime превысить obj.bullet.max_lifetime, необходимо уничтожить
// объект.
//
// Рекомендуемые функции для выполнения задания:
// - Destroy
//
// Возможное решение может занимать примерно 4-5 строк.
// Ваше решение может сильно отличаться.
//
void UpdateBullet(Context &ctx, Object &obj, float dt) {}

// Задание KillEnemies.
//
// Пройдёмся в цикле по объектам сцены (ctx.current_scene), проверяя, что этот
// объект является врагом (obj.enemy.enabled). Если он не враг, то рассматривать
// его дальше не следует.
//
// Затем, внутри цикла, пройдёмся по всем объектам сцены ещё раз. На этот раз в
// поисках пуль. Если у объекта не установлено поле bullet.bullet.enabled, его
// можно не рассматривать дальше.
//
// Затем вызывается функция CheckCollision, которая проверяет, есть ли
// столкновение между врагом и пулей. Если столкновение есть, то оба
// объекта уничтожаются с помощью функции Destroy. Также для объекта
// противника вызывается функция ApplyOnDeath для проигрывания звука.
//
// Рекомендуемые функции для выполнения задания:
// - CheckCollision
// - Destroy
// - ApplyOnDeath
//
// Возможное решение может занимать примерно 14-20 строк.
//
void KillEnemies(Context &ctx) {}

// Задание ApplyOnDeath.
//
// Функция ApplyOnDeath принимает контекст игры ctx и объект obj, на который
// будет применена функция. Функция предназначена для выполнения действий при
// смерти игрока или противника.
//
// В зависимости от типа объекта выбирается и воспроизводится нужный звук.
// Объект может быть игроком, тогда у него активно obj.player.enabled, или
// врагом, тогда у него активно obj.enemy.enabled.
//
// Для реализации необходимо сначала загрузить звук из файла, используя функцию
// LoadSound, после чего воспроизвести его.
//
// Рекомендуемые функции для выполнения задания:
// - LoadSound
// - PlaySound
//
// При реализации данного задания у вас есть возможность добавить свои
// звуки смерти игрока и противников Assets/Sounds/enemy_death.mp3 и
// Assets/Sounds/death.mp3.
//
// Возможное решение может занимать примерно 6-8 строк.
//
void ApplyOnDeath(Context &ctx, Object &obj) {}

// Задание ApplyOnSpawn.
//
// Функция ApplyOnSpawn применяется для объектов, которые только что были
// созданы в игровом мире, и проигрывает звуковой эффект в соответствии с типом
// объекта. Если объект является пулей (obj.bullet.enabled),
// воспроизводится звук выстрела, в противном случае никакой звук не
// воспроизводится.
//
// Для реализации необходимо сначала загрузить звук из файла, используя функцию
// LoadSound, после чего воспроизвести его.
//
// Рекомендуемые функции для выполнения задания:
// - LoadSound
// - PlaySound
//
// При реализации данного задания у вас есть возможность добавить свои
// звуки выстрелов Assets/Sounds/shot.mp3.
//
// Возможное решение может занимать примерно 3 строки.
//
void ApplyOnSpawn(Context &ctx, Object &obj) {}

// Задание DrawDeathScreen.
//
// Данная функция выполняется когда игрок умер от прикосновения к противнику. В
// целом, реализовать эту функцию можно практически как угодно, но минимально
// допустимый вариант - текст, сообщающий о смерти игрока на фоне чёрного
// прямоугольника.
//
// Рекомендуемые функции для выполнения задания:
// - MeasureText
// - DrawRectangle
// - DrawText
//
// Возможное решение может занимать примерно N строк.
//
void DrawDeathScreen(Context &ctx) {}

// Задание DrawGameOverScreen.
//
// Данная функция выполняется когда игрок умер несколько раз и у него
// закончились жизни. В целом, реализовать эту функцию можно практически как
// угодно, но минимально допустимый вариант - текст, сообщающий о проигрыше на
// фоне чёрного прямоугольника.
//
// Рекомендуемые функции для выполнения задания:
// - MeasureText
// - DrawRectangle
// - DrawText
//
// Возможное решение может занимать примерно N строк.
//
void DrawGameOverScreen(Context &ctx) {}

// Задание DrawFinishScreen.
//
// Данная функция выполняется когда игрок дошёл до финиша и прикоснулся к
// нему. В целом, реализовать эту функцию можно практически как угодно, но
// минимально допустимый вариант - текст, сообщающий о победе на фоне чёрного
// прямоугольника.
//
// Рекомендуемые функции для выполнения задания:
// - MeasureText
// - DrawRectangle
// - DrawText
//
// Возможное решение может занимать примерно N строк.
//
void DrawFinishScreen(Context &ctx) {}

// Задание DrawMainScreen.
//
// Функция отрисовывает основной экран игры. Свобода фантазии!
//
// Рекомендуемые функции для выполнения задания:
// - MeasureText
// - DrawText
//
// Возможное решение может занимать примерно N строк.
//
void DrawMainScreen(Context &ctx) {}

bool IsMouseOnButton(Rectangle btn) {
    Vector2 mousePoint = GetMousePosition();
    return CheckCollisionPointRec(mousePoint, btn);
}

void ChangeButtonState(
    Context &ctx,
    Rectangle btnCollider,
    size_t btn_id,
    std::string path1,
    std::string path2
) {
    if (IsMouseOnButton(btnCollider)) {
        for (auto &obj : ctx.current_scene) {
            if (obj.id == btn_id) {
                obj.render = Render(
                    ctx, path2, Vector2(btnCollider.width, btnCollider.height)
                );
            }
        }
    } else {
        for (auto &obj : ctx.current_scene) {
            if (obj.id == btn_id) {
                obj.render = Render(
                    ctx, path1, Vector2(btnCollider.width, btnCollider.height)
                );
            }
        }
    }
}

// Задание ConstructMenuScene.
//
// Функция создаёт объекты в сцене главного меню. Свобода фантазии!
//
// Что можно добавить:
//
// Необходимо создать пустой объект bg, который будет соответствовать фоновой
// картинке. В поле bg.render записать новый объект Render, которая читает
// файл Assets/menu_background.png и задаёт ему размер окна ctx.screen_size.
//
// После этого этот объект нужно добавить в сцену через game_scene.push_back.
//
// Таким же образом можно добавлять любые другие объекты.
//
// Рекомендуемые функции для выполнения задания:
// - Конструктор класса Render
// - Конструктор класса Object
//
// При выполнении этого задания у вас есть возможность добавить любые другие
// текстуры в папку Assets!
//
// Возможное решение может занимать примерно N строк.
//
void ConstructMenuScene(Context &ctx, Scene &game_scene) {
    Object bg = Object();
    bg.render = Render(ctx, "Assets/menu_background2.png", ctx.screen_size);
    game_scene.push_back(bg);

    Object startBtn = Object();
    startBtn.id = 1;
    startBtn.render = Render(ctx, "Assets/start_button1.png", Vector2(200, 50));
    startBtn.position = Vector2(-5, 0);
    game_scene.push_back(startBtn);
}

// Задание DrawStatus.
//
// Функция рисует панель сверху экрана со статусом игры. Свобода фантазии!
//
// В самой панели должны отображаться следующие параметры:
// - Количество жизней игрока. Для этого следует использовать текстуру
//   сердечка, которая сохранена в контексте игры.
//   Для того, чтобы получить саму текстуру сердца можно написать
//     Texture heart_texture = ctx.textures_storage[ctx.heart->hash];
//   После этого текстуру можно использовать функцию DrawTexture.
// - Текущий счёт игрока. Он хранится в поле ctx.score.
// - Время с начала игры. Оно хранится в поле ctx.time в миллисекундах (!!!)
//   Желательно выводить время отдельно в минутах и секундах.
//
// Рекомендуемые функции для выполнения задания:
// - Конструктор класса Render
// - DrawRectangle
// - DrawText
// - MeasureText
// - DrawTexture
//
// При выполнении этого задания у вас есть возможность добавить текстуру
// сердечка Assets/heart.png
//
// Возможное решение может занимать примерно N строк.
//
void DrawStatus(Context &ctx) {}

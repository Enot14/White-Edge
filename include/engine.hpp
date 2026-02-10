#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <Windows.h>
#include <string>
#include <thread>
#include <fstream>
#include <random>
#include "Structs.hpp"
#include "Charters.hpp"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int var = 0;

void pacifist_end() {
    // Пацифість
}

void genocide_end() {
    // геноцид
}

void neutral_end() {
    // нейтрал
}

void changeColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void say(Character c, std::string text, std::string path = "music\\") {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, c.colorCode);
    std::cout << c.name << std::endl;

    int charCount = 0;
    std::string currentPath = path;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 7);
    
    for(char letter : text) {
        std::cout << letter << std::flush;
        if(letter != ' ' && charCount %2 == 0) {
            currentPath = path;
            if(c.name == "???") {
                currentPath += "snd_wngdng" + std::to_string(dis(gen)) + ".wav";
            } else if(c.name == "Максим") {
                currentPath += "snd_txtber.wav";
            } else if(c.name == "????") { //юкі
                currentPath += "snd_txtnoe.wav";
            } else if (c.name == "Анна Петрівна") {
                currentPath += "snd_txttor.wav";
            } else if (c.name == "Мейсен") {
                currentPath += "snd_txtsus.wav";
            } else {
                currentPath += c.voice_path;
            }
            PlaySoundA(currentPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
        }
        charCount++;    
        if(letter == '.'  || letter == '!' || letter == '?') {
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        } else if(letter == ',') {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }else {
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }

    }
    std::cout << std::endl << std::endl;

    SetConsoleTextAttribute(hConsole, 7);
}

void describe(std::string text, std::string path = "music\\SND_TXT1.wav") {
    static int charCount = 0;
    for(char letter : text) {
        std::cout << letter << std::flush;
        if(letter != ' ' && charCount %2 == 0) {
            PlaySoundA(path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
        }
        charCount++;    
        if(letter == '.'  || letter == '!' || letter == '?') {
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        } else if(letter == ',') {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }else {
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }

    }
    std::cout << std::endl << std::endl;
}

void wait(int time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time*1000));
}

int getChoice(int count) {
    int var;
    while (true)
    {
        std::cout << "\n>";
        std::cin >> var;
        if(var >= 1 && var <= count) return var;
        //std::cout << "Обирай мейсене..." << std::endl;
    }
    
}

void saveGame(GameStats state) {
    std::ofstream file("save.dat", std::ios::binary);
    if(file.is_open()) {
        file.write(reinterpret_cast<char*>(&state), sizeof(GameStats));
        file.close();
    }
}

bool loadGame(GameStats &state) {
    std::ifstream file("save.dat", std::ios::binary);
    if(file.is_open()) {
        file.read(reinterpret_cast<char*>(&state), sizeof(GameStats));
        file.close();
        return true;
    }
    return false;
}

void ShowRandomThrought(GameStats &state) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    static std::vector<std::string> darkThoughts = {
        "Вони лише перешкода на твоєму шляху...",
        "Цікаво, як швидко згасне блиск у їхніх очах?",
        "Білий ніж у кишені став занадто важким. Він хоче 'говорити'.",
        "Ти чуєш їхній сміх? Скоро він перетвориться на тишу.",
        "Чому ти досі їх терпиш? У тебе ж є сила..."
    };

    static std::vector<std::string> calmThoughts = {
        "Можливо, у цій музиці є сенс...",
        "Юкі... її погляд був іншим. Чому вона дивилася так?",
        "Сьогодні небо здається не таким сірим.",
        "Ти можеш бути кимось більшим, ніж просто 'ізгой'.",
        "Світ не такий уже й безнадійний, поки вона поруч."
    };

    if(state.karma < 0) {
        state.karma -= 1;
        std::uniform_int_distribution<> dis(0, darkThoughts.size() - 1);
        //Character thoughtVoice = {"Шепіт", 50, 60, 4};
        say(voice_in_head, darkThoughts[dis(gen)]);
    } else {
        state.karma += 1;
        std::uniform_int_distribution<> dis(0, calmThoughts.size() - 1);
        
        //Character thoughtVoice = {"Думка", 200, 50, 11};
        say(voice_in_head, calmThoughts[dis(gen)]);
    }
}

void slowTextW(std::string text, int speed = 200) { //without sound func
    for (char c : text) {
        std::cout << c;
        Sleep(speed);
    }
    std::cout << std::endl;
}

void day_one(GameStats &state) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    describe("Темрява. Лише білий керамбіт відбиває слабке світло місяця.");
    describe("Мейсен стискає руків'я. Книга з бібліотеки не брехала — баланс ідеальний.");
    describe("Від білого ножу надходить холод...");
    describe("Сила в цьому малому...куску металу, яка робила з цим хлопцем невідомі речі.");
    
    say(meisen, "Вона каже, що вони 'золоті'... Цікаво, якого кольору їхня кров...?");
    
    describe("Окрім однієї...");
    describe("Мейсен згадує дівчину з натовпу. Її сміх у натовпі був як збій у системі. Фальшивий.");
    describe("Явно награний, щоб бути як всі.");
    changeColor(4);
    describe("Мусором.");
    changeColor(7);
    describe("Яким вона не є.");
    wait(1);

    Beep(1000, 200);
    Beep(1000, 200);
    
    describe("Різкий звук розрізає тишу. 07:00.");
    describe("Мейсен розплющує очі. Білий ніж лежить поряд з подушкою. Рука все ще пам'ятає його холод.");
    
    say(meisen, "Знову...");
    
    describe("Мейсен одягає форму, ховає керамбіт у шухляду поруч з ліжком і виходить за двері.");

    changeColor(14);
    std::cout << "\n\t--- ГЛАВА 1: ---\n" << std::endl;

    describe("Дорога до школи була тією ж самою.");
    say(meisen, "Однакове.");
    wait(1);
    say(meisen, "Все однакове.");
    wait(1);
    describe("Повторив він у себе в голові");

    describe("Музика грала в навушниках тихо.");
    describe("Мейсен був готовий до всього.");
    describe("Він був на поготові.");
    wait(2);

    describe("\n\nПрийшовши до школи на нього кинули тільки декілька насмішливих поглядів.");
    describe("Мейсен намагався не виділятись, щоб не отримувати ше більше уваги.");
    describe("Але і це йому не допомагало.");

    describe("До пари було ще 15 хвилин.");

    describe("Раптово мейсен почув через музику кроки які зближали дистанцію.");
    describe("За пару секунд на його плечі з'явилась худа долоня.");
    wait(1);
    say(meisen, "Це Максим.");
    describe("Промовив Мейсен в голові, перед тим як зняти навушники і розвернутись.");

    say(Max, "Ну що наш 'обдаровний' учень готовий до контрольної?");
    say(Max, "Ти хоча-б домашку зробив?");
    describe("2 його друга заміялись з цього недожарту.");
    describe("Мейсен просто мовчить."); 
    say(Max, "Ну що ти мовчиш? за слова платиш?");
    describe("Максим наблизив рот до вух Мейсена.");
    describe("І промовив шопотом");
    wait(1);
    say(Max, "Чи надто тупий для цього?");
    describe("Хлопці знову засміялись.");
    wait(1);
    describe("Мейсен промовив в голові.");
    say(meisen, "Це триває кожен день.");
    say(meisen, "Кожен блядський день.");

    wait(2);

    describe("\nПрозвенів звоник, всі заняли свої місця.");
    describe("Мейсен сидів на останній парті свого ряду.");
    describe("Ніби занесений в список 'ізгоїв'.");
    describe("Сидів він очевидно, що сам.");

    describe("Вчителька математики - Анна Петрівна пояснювала, як підписати контрольний зошит, після сказала розбаловку.");
    describe("Зошити почали роздавати.");
    describe("Анна Петрівна поклала зошит на край парти так, ніби боїться забруднити руки об твій стіл. Навіть не глянула в твій бік. Для неї ти — порожнє місце, статистична помилка в її ідеальному звіті.");
    describe("Хлопець на автоматі його підписав.");

    describe("Отримавши завдання, Мейсен глянув на завдання.");
    describe("'початковий рівень'");
    say(meisen, "Як же 'неочінувано'");
    say(meisen, "Вона завжди ставила мене нижче всіх");
    say(meisen, "Нормальне ставленн було тільки до 'золотих' і 'не лінивих' дітей.");
    describe("Мейсену в голову заліз знову той білий ніж...");
    describe("Знову з'явилось бажання поставити цьому кінець");
    describe("Будь-яким способом");
    describe("Що робити?(номер)");
    std::cout << "\n1.Здати пустий лист \t\t 2.Виконати всі завдання\n";

    var = getChoice(2);

    if(var == 1) {
        state.writen_controle = false;
        state.karma -= 10;
        describe("Ви відчуваєте злість на всіх.");
        describe("Листок пролежав пустий до кінця уроку.");
        describe("...");
        wait(1);

        describe("Після дзвонику Мейсен здав лист.");
        say(anna, "Що даже не спробував щось написати?");
        say(anna, "Очікувано...");
        describe("Анна Петрвіна забрала пустий листок і поклала його біля стопки з контрольними");
        wait(1);

        describe("На перерві Мейсен вийшов в коридор.");
        describe("Скоро до нього підійшов Макс з його друзями.");
        say(Max, "хахах, ти даже не додумався підписати лист, тобі твої нейрони не дають таких можливостей?");
        describe("Мейсен видихнув і сказав.");
        say(meisen, "мої нейрони додумались до того, що краще не підписувати лист який могли використати для чогось кориснішого, наприклад...ти міг б ним витерти кров.");
        describe("На мить сміх затих. У коридорі стало занадто холодно.");
        describe("Слова Макса вже були не такими впевненими");
        state.max_agresson -= 4;
        say(Max, "від чого? Чи твоє тіло вже сумнівається в твоїй статі? Місячні почались?");
        describe("Всі почали сміятись.");
        std::cout << "\n1. Відпоісти \t\t 2. Промовчати.\n";
        var = getChoice(2);
        if(var == 1) {
            state.meisen_agresson += 5;
            state.karma -= 5;
            state.max_agresson += 10;
            say(meisen, "Смійся. Поки в тебе ще є легені, щоб виштовхувати повітря. Тобі варто цінувати ці моменти... вони не вічні.");
            describe("Максим дригнувся.");
            describe("Сміх навколо стих.");
            std::cout << "\n1.Продовжити давити \t\t 2. Підти геть\n";
            var = getChoice(2);
            if(var == 1) {
                describe("Мейсен зробив крок вперед, скорочуючи дистанцію до мінімуму.");
                describe("Максим хотів щось бовкнути, але слова застрягли в горлі.");
                
                say(meisen, "Ти такий гучний, Максиме. Але твої очі... вони бігають.");
                say(meisen, "Тобі страшно, що хтось побачить, який ти насправді порожній без своєї 'свити'?");
                
                describe("Мейсен поклав руку на плече Максима. Не грубо, але пальці стиснули тканину форми.");
                
                say(meisen, "Цікаво... скільки ще ти зможеш тримати цю маску 'золотої дитини', поки вона не трісне від страху?");
                
                describe("У коридорі панувала гробова тиша. Навіть друзі Максима відступили на крок.");
                describe("Серед загального заціпеніння лише одне обличчя залишалося нерухомим...");
                
                say(Max, "Т-ти... ти просто хворий на голову!");
                
                describe("Максим скинув руку Мейсена і швидко пішов геть, намагаючись не бігти.");
                describe("Його друзі поплелися слідом, постійно озираючись.");
                state.max_agresson += 25;
                state.karma -= 10;
            } else {
                describe("Мейсен розвернувся і пішов у невідомому напрямку.");
                state.karma += 10;
            }
        } else {
            state.meisen_agresson +=5;
            state.karma +=5;
            state.max_agresson += 5;
            describe("Ви вирішили, що краше промовчати.");
            say(Max, "Що язик лигнув?");
            say(Max, "Ало! відповідай!");
            describe("Максим легко б'є в плече Мейсена.");
            std::cout << "\n1. Відпоісти \t\t 2. Продовжити ігнорувати.\n";
            var = getChoice(2);
            if(var == 1) {
                state.max_agresson += 25;
                state.karma -= 10;
                state.meisen_agresson += 10;
                state.yuki_trust += 1;
                say(meisen, "Язик я не лигнув, просто знаю коли краще його тримати за зубами");
                say(meisen, "А ти я бачу ні.");
                say(meisen, "Тоді надалі не жалійся, що в тебе його не стане.");
                describe("Навкруги запанувала тиша...");
                describe("Ніхто не очікував такої агресивної відповіді.");
                describe("Мейсен підняв більш впевнений погляд з неменш впевненою ухмилкою.");
                say(Max, "Та що ти верзеш взагалі?!");
                describe("Та Мейсен відповів таким ж спокійним тоном.");
                changeColor(4);
                say(meisen, "Те що може статися з тобою.");
                changeColor(7);
                say(Max, "Ей хлопці, я думаю краще підти від цього скаженого.");
                say(Max, "а то ми ще опустимось до його рівня.");
                describe("Максим старався говорити впевненіше, але в нього це не добре виходило.");
                describe("Натовп по троху розходився і останньою пішла а сама дівчина, чиє ім'я досі не знав Мейсен.");
                describe("Перед тим як сховатись у натовпі вона кинула на нього приємний погляд з такою ж посмішкою.");
            } else {
                state.karma += 5;
                state.meisen_agresson += 1;
                state.max_agresson += 5;
                describe("Ви продовжили ігнорувати Максима.");
                say(Max, "Що мізків хватило тільки 1 раз відповісти?");
                say(Max, "Я й не сумнівався в тому наскільки ти тупий.");
                say(Max, "Ходімо хлопці, а то ще деградуємо поряд.");
                describe("Максим та його помпанія пішли геть і залиши Мейсена в більш тихій обстановці.");
                describe("Осьтанньою пішла та сама дівчина, та чиєї ім'я Мейсен не знав.");
                describe("Вона подивилась на нього трохи сумно і після цього просто пішла геть в тому ж напрямку.");
            }
        }
    } else {
        state.writen_controle = true;
        state.karma += 5;
        state.yuki_trust += 2;
        describe("Ви вирішили не давати їи приводу для знущань.");
    }

    wait(2);
    describe("Минуло 2 уроки.");
    describe("Мейсен сидить с столовій. Один. Як завжди");
    describe("Він їсть і помічає як Максим сідає за стіл до тієї дівчини. Яка не як всі сміялась.");
    describe("В столовій доволі гучно, та деякі уривки фраз можна почути");
    say(Max, "Чому ти одна? давай я тобі зіставлю компанію.");
    say(Max, "Невже ти не хочеш щоб я провів з тобою час?");
    say(yuki, "Я хочу побути на самоті.");
    describe("Вперше, Мейсен почув цей мелодійний голос.");
    say(Max, "Да ну, ти відмовляєшся щоб я з тобою сидів?..");
    say(Max, "Тоді я буду сидіти не з тобою, а за столом, просто за ним сидиш ти також.");
    say(yuki, "...");
    describe("Мейсен розумів як це погано виглядає зі сторони, та поки нічого зробити з цим не міг.");
    describe("Він продовжив їсти на спостерігати за цим видовищем.");
    describe("Максим продовжував щось говорити.");
    say(Max, "...Невже ти хочеш бути такою ж самотньою як той 'обдарований'?");
    describe("Дівчина почала окидувати столову поглядом в пошуках того, про кого говорить Максим.");
    describe("Раптом вона зустрічається з поглядом Мейсена. Секунду тривав цей зоровий контакт, після вона розвернулась назад.");
    describe("Максим знову щось розказував, намагаючись торкнутися дівчини");
    describe("Невдовзі продзвинів дзвоник і столова почала спустошуватись. Мейсен піднявся і направився на урок.");

    wait(2);
    describe("Минуло ще 4 уроки.");
    wait(2);

    describe("Мейсен сидів на останньому уроці - Малюванні");
    describe("Хлопець розумів, що Максим постарається відігратись, а коли школа пуста в нього більше можливостей");
    describe("У хлопця був вибір, втекти на останніх 5-ти хвилинах чи залишитись");
    std::cout << "\n1.Залишитись \t\t 2. Втекти\n";
    var = getChoice(2);
    if(var == 1) {
        state.karma -= 15;
        state.max_agresson += 20; 

        describe("Дзвінок пролунав, але він здавався якимось тривожним.");
        describe("Мейсен повільно зібрав речі. Коли він вийшов у коридор, там уже майже нікого не було.");
        describe("Тільки відлуння його власних кроків... і ще чиїсь.");

        wait(1);
        describe("Біля виходу шлях перегородили троє. Максим і його вірні 'тіні'.");
        
        say(Max, "Ну що, 'філософе', знову застряг у своїх думках?");
        say(Max, "Ти сьогодні багато говорив у коридорі. Принижував мене перед усіма... Думав, я забуду?");
        describe("Максим зробив крок вперед. Тепер він не боявся. Поруч не було вчителів чи інших учнів.");
        say(meisen, "Ти привів друзів, щоб просто поговорити? Цікаво.");
        describe("Удар у живіт прийшов раптово. Повітря миттєво покинуло легені Мейсена.");
        describe("Він впав на коліна, намагаючись вхопити бодай ковток кисню.");
        say(Max, "Це за 'нейрони'. А це — за 'легені'!");
        describe("Максим штовхнув Мейсена ногою в плече, збиваючи на холодну підлогу.");
        describe("Вони не били довго. Просто хотіли показати, хто тут господар.");
        
        wait(2);
        describe("Через пару хвилин усе скінчилося. Максим витер руки об хустку.");
        say(Max, "Завтра будь тихіше, сміття. Бо наступного разу ми витремо твою кров твоїм же порожнім зошитом.");
        describe("Вони пішли, сміючись. Мейсен залишився лежати в напівтемряві.");
        describe("В роті відчувався металевий присмак крові. А в душі — крижаний спокій.");
        
        state.meisen_agresson += 30; 
    } else {
        state.karma -= 5;
        describe("Мейсен спокійно просидів, доки не залишилось 5 хвилин до кінця уроку.");
        describe("Все було і так зібрано, тому Мейсен просто піднявся і пішов.");
        describe("На щаста, може і не на щастя Максим цього не бачив.");
        describe("Хлопець просто спокійно вискакнув з класу і пішов додому.");
    }
    if(var == 1) {
        describe("Прийшовши додому Мейсен увалився на ліжко в одежі.");
        describe("Хлопець відчував себе набагато гірше");
    } else {
        describe("Прийшовши додому Мейсен сів на ліжко і видихнув.");
    }

    say(meisen, "Цікаво як її звати?");
    say(meisen, "Може колись я все-таки дізнаюсь...");
    say(meisen, "Батьки знову будуть пізно...може взагалі не прийдуть.");
    say(meisen, "Неважливо...");
    describe("Хлопець видихнув.");
    if(state.karma < 20) {
        say(meisen, "Таке дивне відчуття...");
        say(meisen, "На диво воно приємне.");
    }
    wait(1);
    describe("\nВечір накрив місто. Мейсен сів за стіл.");
    describe("На столі — блокнот. У шухляді — білий керамбіт.");
    describe("Що робити сьогодні ввечері?");
    std::cout << "\n1. Спробувати писати музику \t\t 2. Тренуватися з ножем\n";

    var = getChoice(2);

    if(var == 1) {
        state.karma += 15;
        describe("Мейсен взяв ручку. Папір вбирав слова, а не кров.");
        say(meisen, "Може... музика — це єдине, що в мені ще не згнило.");
    } else {
        state.karma -= 20;
        state.knife_skill += 15;
        describe("Він дістав керамбіт. Холодна сталь ідеально лягла в побиту руку.");
        describe("Удар. Ще удар. Повітря розривалося зі свистом.");
        say(meisen, "Наступного разу... витирати кров буду я.");
        describe("Мейсен дістав книгу і почав читати про керамбіт. Куди і як краще бити.");
        describe("Запам'ятовувати куди краще було бити не важко.");
        describe("Але техніка була ще далеко не кращою.");
    }
}

void ShowRandomThrought(const GameStats &state) {
    if(state.karma < 20) {
        describe("У вашій голові звучить тихий і невідомий шепот... 'Вони лише перешкода'.");
    }
}

void notification(int count, std::string path = "music\\snd_textnoise.wav") {
    for(int i = 0; i < count; i++) {
        PlaySoundA(path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
        std::cout << "LOG " << i << std::flush << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void day_two(GameStats &state) {
    system("cls");
    //Beep(1000, 200);
    //Beep(1000, 200);
    int var = 1;
    
    describe("Різкий звук розрізає тишу. 07:00.");
    //slowText("lox pisun lox pidar");
    //notification(2);
    describe("Це було повідомлення від классної керівнички, що останнього уроку не буде.");
    /*describe("Мейсен розплющив очі.");
    if(var == 1) {
        describe("На тумбочці поряд з ліжком лежить листок з написами пісні.");
    } else {
        describe("На тумбочні поряд з ліжком лежить повністю білий керамбіт.");
        describe("Даже з ранковим сонцем він світиться світліше за все в кімнаті.");
    }
    describe("Мейсен спокійно піднявся з ліжка і пішов збиратись.");
    describe("Перед виходом Мейсен подивився на тумбочку знову.");
    if(var == 1) {
        say(meisen, "Може взяти листок з собою? Може натхнення буде.");
        describe("1.Взяти листок з собою.");
        describe("2.Лишити листок.");
        var =getChoice(2);
        if(var == 1) {
            state.leaf = true;
            describe("Мейсен забирає оисток і закидає його в рюкзак.");
            say(meisen, "Може це і на краще.");
        } else {
            describe("Ви вирішили, що краще залишити листок вдома.");
        }
    } else {
        say(meisen, "");
    }*/
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#endif
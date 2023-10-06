#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;
#define NOMINMAX
#include <Windows.h>

class AudioFile {
private:
    std::string fileName;
    std::string artistName;
    std::string trackName;
    int duration;
    int releaseYear;
public:
    AudioFile(
        const std::string& fileName = "имя_файла.mp3",
        const std::string& artistName = "Имя Артиста",
        const std::string& trackName = "Название трека",
        int duration = 0,
        int releaseYear = 1999
    );

    void output(bool isLong = true) const;
    void shortOutput();
    void setTrackName(const std::string trackName);

    std::string getArtistName();
    std::string getTrackName();
    int getDuration();
    int getReleaseYear();
};

class Playlist {
private:
    std::string playlistName;
    std::vector<AudioFile> list;
public:
    Playlist(const std::string& playlistName, std::vector<AudioFile> list);

    void output(bool isLong = true);
    void add(const AudioFile& elem);
    void remove(int index);

    std::string& getPlaylistName();
    int getListSize();
    AudioFile& getElement(int index);

    void setPlaylistName(const std::string& newPlaylistName);
};

class AudioPlayer {
private:
    bool isPlaylistAssigned = false;
    bool isPlaying = false;
    Playlist* currPlaylist;
    int trackIndexInPlaylist;
public:
    AudioPlayer();
    AudioPlayer(Playlist* currPlaylist, int trackIndexInPlaylist = 0);

    void play();
    void pause();
    bool toggle();
    AudioFile& next();
    AudioFile& previous();

    AudioFile& getCurrentTrack();
    bool getIsPlaylistAssignedStatus();
    bool getIsPlayingStatus();

    void setPlaylist(Playlist* newPlaylist);
};

class AudioCollection {
private:
    std::vector<AudioFile> list;
public:
    AudioCollection(std::vector<AudioFile> list = std::vector<AudioFile>());

    void add(const AudioFile& elem);
    void remove(int index);

    std::vector<AudioFile> searchByArtistName(const std::string& artistName);
    std::vector<AudioFile> searchByReleaseYear(int releaseYear);

    void printSearchResults(const std::vector<AudioFile>& results);
    void searchAndPrintByArtistName(const std::string& artistName);
    void searchAndPrintByReleaseYear(int releaseYear);

    void printStats();
};

class MusicLibrary {
private:
    std::vector<AudioFile> audioFileArray;
    std::vector<Playlist> playlistArray;
public:
    MusicLibrary(std::vector<AudioFile> audioFileArray = std::vector<AudioFile>(), std::vector<Playlist> playlistArray = std::vector<Playlist>());

    AudioFile& createAudioFile();
    Playlist& createPlaylist();

    int printAudioFileArray();
    int printPlaylistArray();

    std::vector<AudioFile> getAudioFileArray();
    int getPlaylistArraySize();
    Playlist& getPlaylistByIndex(int index);

    ~MusicLibrary();
};

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MusicLibrary lib; // библиотека треков
    AudioPlayer player; // аудиоплеер

    // меню
    int quit = 0;

    while (!quit) {
        std::cout << "Список команд" << std::endl;
        std::cout << "1. Создать аудиофайл" << std::endl;
        std::cout << "2. Создать плейлист" << std::endl;
        std::cout << "3. Вывести список созданных треков" << std::endl;
        std::cout << "4. Вывести список созданных плейлистов" << std::endl;
        std::cout << "5. Поиск треков по имени исполнителя" << std::endl;
        std::cout << "6. Поиск треков по году выхода" << std::endl;
        std::cout << "7. Редактировать плейлист" << std::endl;
        std::cout << "8. Аудиоплеер" << std::endl;
        std::cout << "0. Выход" << std::endl;

        int command;
        do {
            std::cout << "Введите команду: ";
            std::cin >> command;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера ввода
        } while (command < 0 || command > 8);

        switch (command) {
        case 0:
            std::cout << "Выход..." << std::endl;
            quit = 1;
            break;
        case 1:
            std::cout << "Создать аудиофайл" << std::endl;
            lib.createAudioFile();
            break;
        case 2:
            std::cout << "Создать плейлист" << std::endl;
            lib.createPlaylist();
            break;
        case 3:
            std::cout << "Вывести список созданных треков" << std::endl;
            lib.printAudioFileArray();
            break;
        case 4:
            std::cout << "Вывести список созданных плейлистов" << std::endl;
            lib.printPlaylistArray();
            break;
        case 5: {
            std::cout << "Поиск треков по имени исполнителя" << std::endl;

            std::string artistName;
            std::cout << "Введите имя исполнителя: ";
            std::getline(std::cin, artistName);

            AudioCollection collection(lib.getAudioFileArray());
            collection.searchAndPrintByArtistName(artistName);
        } break;
        case 6: {
            std::cout << "Поиск треков по году выхода" << std::endl;

            int releaseYear;
            std::cout << "Введите год выхода: ";
            std::cin >> releaseYear;

            AudioCollection collection(lib.getAudioFileArray());
            collection.searchAndPrintByReleaseYear(releaseYear);
        } break;
        case 7: {
            std::cout << "Редактировать плейлист" << std::endl;

            if (lib.getPlaylistArraySize() == 0) {
                std::cout << "Редактирование плейлиста невозможно: нет плейлистов в библиотеке" << std::endl;
                break;
            }

            lib.printPlaylistArray();

            int playlistNumber;
            do {
                std::cout << "Введите номер плейлиста: ";
                std::cin >> playlistNumber;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера ввода
            } while (playlistNumber < 1 || playlistNumber > lib.getPlaylistArraySize());

            Playlist& chosenPlaylist = lib.getPlaylistByIndex(playlistNumber - 1);

            int answer;
            do {
                do {
                    std::cout << "Меню работы с плейлистом" << std::endl;
                    std::cout << "1. Изменение названия плейлиста" << std::endl;
                    std::cout << "2. Добавление трека в плейлист" << std::endl;
                    std::cout << "3. Удаление трека из плейлиста" << std::endl;
                    std::cout << "4. Вывод списка треков плейлиста" << std::endl;
                    std::cout << "0. Завершить редактирование плейлиста" << std::endl;

                    std::cout << "Введите команду: ";
                    std::cin >> answer;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера ввода
                } while (answer < 0 || answer > 4);

                switch (answer) {
                case 0:
                    std::cout << "Завершение работы по редактированию плейлиста" << std::endl;
                    break;
                case 1: {
                    std::cout << "Изменение названия плейлиста" << std::endl;

                    std::string newPlaylistName;
                    std::cout << "Введите новое название плейлиста: ";
                    std::getline(std::cin, newPlaylistName);

                    chosenPlaylist.setPlaylistName(newPlaylistName);
                    std::cout << "Название плейлиста изменено на \"" << newPlaylistName << "\"" << std::endl;
                } break;
                case 2: {
                    std::cout << "Добавление трека в плейлист" << std::endl;

                    AudioFile& createdAudioFile = lib.createAudioFile();
                    chosenPlaylist.add(createdAudioFile);

                    std::cout << "Трек добавлен в плейлист" << std::endl;
                } break;
                case 3: {
                    std::cout << "Удаление трека из плейлиста" << std::endl;

                    chosenPlaylist.output(false);

                    int chosenTrackNumber;
                    do {
                        std::cout << "Введите номер трека для удаления: ";
                        std::cin >> chosenTrackNumber;
                    } while (chosenTrackNumber < 1 || chosenTrackNumber > chosenPlaylist.getListSize());

                    chosenPlaylist.remove(chosenTrackNumber - 1);
                    std::cout << "Выбранный трек удален из плейлиста" << std::endl;
                } break;
                case 4:
                    std::cout << "Вывод списка треков плейлиста" << std::endl;

                    chosenPlaylist.output(false);
                    break;
                }
            } while (answer != 0);

        } break;
        case 8: {
            int answer;
            do {
                do {
                    bool isPlaying = player.getIsPlayingStatus();
                    bool isPlaylistAssigned = player.getIsPlaylistAssignedStatus();

                    std::cout << "Аудиоплеер" << std::endl;
                    if (isPlaylistAssigned) {
                        if (isPlaying)
                            std::cout << "Статус: играет" << std::endl;
                        else
                            std::cout << "Статус: не играет" << std::endl;
                        std::cout << "Текущий трек: " << player.getCurrentTrack().getTrackName() << ". ";
                        std::cout << "Исполнитель: " << player.getCurrentTrack().getArtistName() << std::endl;
                    }
                    else
                        std::cout << "Статус: плейлист не определен" << std::endl;

                    std::cout << "Меню управления аудиоплеером" << std::endl;
                    std::cout << "1. Назначить плейлист" << std::endl;
                    std::cout << "2. Play/Pause" << std::endl;
                    std::cout << "3. Следующий трек" << std::endl;
                    std::cout << "4. Предыдущий трек" << std::endl;
                    std::cout << "0. Выход в главное меню" << std::endl;

                    std::cout << "Введите команду: ";
                    std::cin >> answer;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера ввода
                } while (answer < 0 || answer > 4);

                switch (answer) {
                case 0:
                    std::cout << "Возвращение к меню..." << std::endl;
                    break;
                case 1: {
                    std::cout << "Назначить плейлист" << std::endl;

                    if (lib.getPlaylistArraySize() == 0) {
                        std::cout << "Ошибка: нет плейлистов в библиотеке" << std::endl;
                        break;
                    }

                    lib.printPlaylistArray();

                    int playlistNumber;
                    do {
                        std::cout << "Введите номер плейлиста: ";
                        std::cin >> playlistNumber;
                    } while (playlistNumber < 1 || playlistNumber > lib.getPlaylistArraySize());

                    Playlist& chosenPlaylist = lib.getPlaylistByIndex(playlistNumber - 1);
                    player.setPlaylist(&chosenPlaylist);
                    std::cout << "Выбранный плейлист назначен" << std::endl;
                } break;
                case 2: {
                    std::cout << "Изменить статус проигрывания" << std::endl;

                    player.toggle();
                    std::cout << "Статус изменен" << std::endl;
                } break;
                case 3: {
                    std::cout << "Следующий трек" << std::endl;

                    player.next();
                    std::cout << "Трек в плеере изменен" << std::endl;
                } break;
                case 4: {
                    std::cout << "Предыдущий трек" << std::endl;

                    player.previous();
                    std::cout << "Трек в плеере изменен" << std::endl;
                } break;
                }
            } while (answer != 0);
        } break;
        }
    }
}

AudioFile::AudioFile(const std::string& fileName, const std::string& artistName, const std::string& trackName, int duration, int releaseYear) {
    this->fileName = fileName;
    this->artistName = artistName;
    this->trackName = trackName;
    this->duration = duration;
    this->releaseYear = releaseYear;
}

void AudioFile::output(bool isLong) const
{
    if (isLong) { // длинная версия
        std::cout << "Название трека: " << trackName << std::endl;
        std::cout << "Исполнитель: " << artistName << std::endl;
        std::cout << "Имя файла: " << fileName << std::endl;
        std::cout << "Длительность (в с): " << duration << std::endl;
        std::cout << "Год выхода: " << releaseYear << std::endl;
    }
    else { // короткая версия
        std::cout << artistName << " - " << trackName << ", "
            << duration << "s" << ", " << releaseYear << " - " << fileName << std::endl;
    }
}

void AudioFile::shortOutput()
{
    output(false);
}

void AudioFile::setTrackName(const std::string trackName)
{
    this->trackName = trackName;
}

std::string AudioFile::getArtistName()
{
    return artistName;
}

std::string AudioFile::getTrackName()
{
    return trackName;
}

int AudioFile::getDuration()
{
    return duration;
}

int AudioFile::getReleaseYear()
{
    return releaseYear;
}

Playlist::Playlist(const std::string& playlistName, std::vector<AudioFile> list)
{
    this->playlistName = playlistName;
    this->list = list;
}

void Playlist::output(bool isLong)
{
    std::cout << "Плейлист \"" << playlistName << "\"" << std::endl;

    int listLength = list.size();
    for (int i = 0; i < listLength; i++) {
        std::cout << i + 1 << ". ";
        list[i].output(isLong);
    }
}

void Playlist::add(const AudioFile& elem)
{
    list.push_back(elem);
}

void Playlist::remove(const int index)
{
    if (index >= 0 && index < list.size()) {
        list.erase(list.begin() + index);
    }
}

std::string& Playlist::getPlaylistName()
{
    return playlistName;
}

int Playlist::getListSize()
{
    return list.size();
}

AudioFile& Playlist::getElement(int index)
{
    return list[index];
}

void Playlist::setPlaylistName(const std::string& newPlaylistName)
{
    playlistName = newPlaylistName;
}

AudioPlayer::AudioPlayer()
    : currPlaylist(currPlaylist), trackIndexInPlaylist(trackIndexInPlaylist)
{
    isPlaylistAssigned = false;
}

AudioPlayer::AudioPlayer(Playlist* currPlaylist, int trackIndexInPlaylist)
    : currPlaylist(currPlaylist), trackIndexInPlaylist(trackIndexInPlaylist)
{
    this->currPlaylist = currPlaylist;
    this->isPlaylistAssigned = true;
    this->trackIndexInPlaylist = trackIndexInPlaylist;
}

void AudioPlayer::play()
{
    isPlaying = true;
}

void AudioPlayer::pause()
{
    isPlaying = false;
}

bool AudioPlayer::toggle()
{
    isPlaying = !isPlaying;
    return isPlaying;
}

AudioFile& AudioPlayer::next()
{
    if (trackIndexInPlaylist + 1 < currPlaylist->getListSize())
        trackIndexInPlaylist++;
    return getCurrentTrack();
}

AudioFile& AudioPlayer::previous()
{
    if (trackIndexInPlaylist > 0)
        trackIndexInPlaylist--;
    return getCurrentTrack();
}

void AudioPlayer::setPlaylist(Playlist* newPlaylist)
{
    currPlaylist = newPlaylist;
    isPlaylistAssigned = true;
}

AudioFile& AudioPlayer::getCurrentTrack()
{
    return currPlaylist->getElement(trackIndexInPlaylist);
}

bool AudioPlayer::getIsPlaylistAssignedStatus()
{
    return isPlaylistAssigned;
}

bool AudioPlayer::getIsPlayingStatus()
{
    return isPlaying;
}

AudioCollection::AudioCollection(std::vector<AudioFile> list)
{
    this->list = list;
}

void AudioCollection::add(const AudioFile& elem)
{
    list.push_back(elem);
}

void AudioCollection::remove(int index)
{
    if (index >= 0 && index < list.size()) {
        list.erase(list.begin() + index);
    }
}

std::vector<AudioFile> AudioCollection::searchByArtistName(const std::string& artistName)
{
    std::vector<AudioFile> result = std::vector<AudioFile>();

    int listSize = list.size();
    for (int i = 0; i < listSize; i++) {
        AudioFile& currTrack = list[i];
        if (currTrack.getArtistName() == artistName)
            result.push_back(currTrack);
    }

    return result;
}

std::vector<AudioFile> AudioCollection::searchByReleaseYear(int releaseYear)
{
    std::vector<AudioFile> result = std::vector<AudioFile>();

    int listSize = list.size();
    for (int i = 0; i < listSize; i++) {
        AudioFile& currTrack = list[i];
        if (currTrack.getReleaseYear() == releaseYear)
            result.push_back(currTrack);
    }

    return result;
}

void AudioCollection::printSearchResults(const std::vector<AudioFile>& results)
{
    int resultsCount = results.size();

    if (resultsCount == 0) {
        std::cout << "Ничего не найдено" << std::endl;
        return;
    }

    std::cout << "Результаты поиска" << std::endl;
    for (int i = 0; i < resultsCount; i++) {
        const AudioFile& currAudioFile = results[i];
        std::cout << (i + 1) << ". ";
        currAudioFile.output(false);
    }
}

void AudioCollection::searchAndPrintByArtistName(const std::string& artistName)
{
    std::vector<AudioFile> results = searchByArtistName(artistName);
    printSearchResults(results);
}

void AudioCollection::searchAndPrintByReleaseYear(int releaseYear)
{
    std::vector<AudioFile> results = searchByReleaseYear(releaseYear);
    printSearchResults(results);
}

void AudioCollection::printStats()
{
    int tracksCount = list.size(); // количество треков
    int fullDuration = 0; // длительность всех треков в коллекции
    for (int i = 0; i < tracksCount; i++) {
        AudioFile& file = list[i];
        fullDuration += file.getDuration();
    }
    double averageDuration = (double)fullDuration / tracksCount; // средняя длительность

    std::cout << "Количество треков: " << tracksCount << std::endl;
    std::cout << "Полная длительность треков: " << fullDuration << std::endl;
    std::cout << "Средняя длительность трека: " << averageDuration << std::endl;
}

MusicLibrary::MusicLibrary(std::vector<AudioFile> audioFileArray, std::vector<Playlist> playlistArray)
{
    this->audioFileArray = audioFileArray;
    this->playlistArray = playlistArray;
}

AudioFile& MusicLibrary::createAudioFile()
{
    std::cout << "Создание карточки трека" << std::endl;

    std::string fileName, artistName, trackName;
    int duration, releaseYear;

    std::cout << "Введите наименование файла: ";
    std::getline(std::cin, fileName);
    std::cout << "Введите имя артиста: ";
    std::getline(std::cin, artistName);
    std::cout << "Введите название трека: ";
    std::getline(std::cin, trackName);
    std::cout << "Введите длительность трека (в с): ";
    std::cin >> duration;
    std::cout << "Введите год выхода трека: ";
    std::cin >> releaseYear;

    AudioFile* audioFile = new AudioFile(fileName, artistName, trackName, duration, releaseYear);
    std::cout << "Трек создан" << std::endl;

    audioFileArray.push_back(*audioFile);
    return *audioFile;
}

Playlist& MusicLibrary::createPlaylist()
{
    std::cout << "Создание плейлиста" << std::endl;

    std::string playlistName;
    std::vector<AudioFile> list;

    std::cout << "Введите название плейлиста: ";
    std::getline(std::cin, playlistName);

    bool quit = 0;
    do {
        std::cout << "Добавление трека в плейлист" << std::endl;
        std::cout << "1. Добавить трек из библиотеки" << std::endl;
        std::cout << "2. Создать карточку трека и добавить его в плейлист" << std::endl;
        std::cout << "0. Завершить добавление треков (невозможно, если не был добавлен хотя бы 1 трек в плейлист)" << std::endl;

        int answer;
        do {
            std::cout << "Выбор (0-2): ";
            std::cin >> answer;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера ввода
        } while (answer < 0 || answer > 2);

        switch (answer) {
        case 0: // заврешение
            std::cout << "Создаем плейлист..." << std::endl;
            quit = true;
            break;
        case 1: { // добавление трека из библиотеки
            std::cout << "Добавление трека из библиотеки" << std::endl;

            int audioFileArraySize = audioFileArray.size();
            if (audioFileArraySize == 0)
                std::cout << "Невозможно добавить трек из библиотеки: список треков пуст" << std::endl;
            else {
                printAudioFileArray();

                do {
                    std::cout << "Выбранный трек: ";
                    std::cin >> answer;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера ввода
                } while (answer < 1 || answer > audioFileArraySize);

                AudioFile& chosenTrack = audioFileArray[answer - 1];
                list.push_back(chosenTrack);
                std::cout << "Выбранный трек добавлен" << std::endl;
            }
        } break;
        case 2: // создание трека
            AudioFile& createdAudioFile = createAudioFile();
            list.push_back(createdAudioFile);
            std::cout << "Созданный трек добавлен в плейлист" << std::endl;
            break;
        }
    } while (!quit);

    Playlist playlist(playlistName, list);
    playlistArray.push_back(playlist);
    return playlist;
}

int MusicLibrary::printAudioFileArray()
{
    int arraySize = audioFileArray.size();

    if (arraySize == 0)
        std::cout << "Список треков пуст" << std::endl;
    else {
        std::cout << "Список треков: " << std::endl;

        for (int i = 0; i < arraySize; i++) {
            AudioFile& currTrack = audioFileArray[i];
            std::cout << (i + 1) << ". "; currTrack.shortOutput();
        }
    }

    return arraySize;
}

int MusicLibrary::printPlaylistArray()
{
    int arraySize = playlistArray.size();
    
    if (arraySize == 0)
        std::cout << "Список плейлистов пуст" << std::endl;
    else {
        std::cout << "Список плейлистов: " << std::endl;

        for (int i = 0; i < arraySize; i++) {
            Playlist& currPlaylist = playlistArray[i];
            std::cout << (i + 1) << ". " << currPlaylist.getPlaylistName()
                << " - " << currPlaylist.getListSize() << " треков" << std::endl;
        }
    }

    return arraySize;
}

std::vector<AudioFile> MusicLibrary::getAudioFileArray()
{
    return audioFileArray;
}

int MusicLibrary::getPlaylistArraySize()
{
    return playlistArray.size();
}

Playlist& MusicLibrary::getPlaylistByIndex(int index)
{
    return playlistArray[index];
}

MusicLibrary::~MusicLibrary()
{
    for (int i = 0; i < audioFileArray.size(); i++) {
        delete &audioFileArray[i];
    }
}

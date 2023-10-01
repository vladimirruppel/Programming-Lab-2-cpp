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

    void output(bool isLong = true);
    void shortOutput();
    void setTrackName(const std::string trackName);

    std::string getArtistName();
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
};

class AudioPlayer {
private:
    bool isPlaying = 0;
    Playlist& currPlaylist;
    int trackIndexInPlaylist;
public:
    AudioPlayer(Playlist& currPlaylist, int trackIndexInPlaylist = 0);

    void play();
    void pause();
    bool toggle();
    AudioFile& next();
    AudioFile& previous();
    void setPlaylist(Playlist& newPlaylist);
    AudioFile& getCurrentTrack();
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
};

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MusicLibrary lib; // библиотека треков

    // меню
    int quit = 0;

    while (!quit) {
        std::cout << "Список команд" << std::endl;
        std::cout << "1. Создать аудиофайл" << std::endl;
        std::cout << "2. Создать плейлист" << std::endl;
        std::cout << "3. Вывести список созданных треков" << std::endl;
        std::cout << "4. Вывести список созданных плейлистов" << std::endl;
        std::cout << "0. Выход" << std::endl;

        int command;
        do {
            std::cout << "Введите команду: ";
            std::cin >> command;
        } while (command < 0 || command > 4);

        switch (command) {
        case 0:
            std::cout << "Выход..." << std::endl;
            quit = 1;
            break;
        case 1:
            std::cout << "Создать аудиофайл" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера ввода
            lib.createAudioFile();
            break;
        case 2:
            std::cout << "Создать плейлист" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера ввода
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
        }
    }
}

AudioFile::AudioFile(
    const std::string& fileName,
    const std::string& artistName,
    const std::string& trackName,
    int duration,
    int releaseYear
) {
    this->fileName = fileName;
    this->artistName = artistName;
    this->trackName = trackName;
    this->duration = duration;
    this->releaseYear = releaseYear;
}

void AudioFile::output(bool isLong)
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

AudioPlayer::AudioPlayer(Playlist& currPlaylist, int trackIndexInPlaylist)
    : currPlaylist(currPlaylist), trackIndexInPlaylist(trackIndexInPlaylist)
{
    this->currPlaylist = currPlaylist;
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
    if (trackIndexInPlaylist + 1 < currPlaylist.getListSize())
        trackIndexInPlaylist++;
    return getCurrentTrack();
}

AudioFile& AudioPlayer::previous()
{
    if (trackIndexInPlaylist > 0)
        trackIndexInPlaylist--;
    return getCurrentTrack();
}

void AudioPlayer::setPlaylist(Playlist& newPlaylist)
{
    currPlaylist = newPlaylist;
}

AudioFile& AudioPlayer::getCurrentTrack()
{
    return currPlaylist.getElement(trackIndexInPlaylist);
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

    std::cout << "Введите наименование файла" << std::endl;
    std::getline(std::cin, fileName);
    std::cout << "Введите имя артиста" << std::endl;
    std::getline(std::cin, artistName);
    std::cout << "Введите название трека" << std::endl;
    std::getline(std::cin, trackName);
    std::cout << "Введите длительность трека" << std::endl;
    std::cin >> duration;
    std::cout << "Введите год выхода трека" << std::endl;
    std::cin >> releaseYear;

    AudioFile audioFile(fileName, artistName, trackName, duration, releaseYear);
    std::cout << "Трек создан" << std::endl;

    audioFileArray.push_back(audioFile);
    return audioFile;
}

Playlist& MusicLibrary::createPlaylist()
{
    std::cout << "Создание плейлиста" << std::endl;

    std::string playlistName;
    std::vector<AudioFile> list;

    std::cout << "Введите название плейлиста" << std::endl;
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
        } while (answer < 0 || answer > 2);

        switch (answer) {
        case 0: // заврешение
            std::cout << "Создаем плейлист...";
            quit = true;
            break;
        case 1: { // добавление трека из библиотеки
            std::cout << "Добавление трека из библиотеки" << std::endl;

            int audioFileArraySize = audioFileArray.size();
            if (audioFileArraySize == 0)
                std::cout << "Невозможно добавить трек из библиотеки: список треков пуст";
            else {
                printAudioFileArray();

                do {
                    std::cout << "Выбранный трек: ";
                    std::cin >> answer;
                } while (answer < 1 || answer > audioFileArraySize);

                AudioFile& chosenTrack = audioFileArray.at(answer);
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

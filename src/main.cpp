#include "QuakeAssistController.h"
#include <iostream>
#include <fstream>
#include <string>

// This main file is provided for you.
// It reads commands from the given input file and forwards them
// to the QuakeAssistController. You do NOT need to modify main.cpp.

int main(int argc, char* argv[]) {
    /*std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    QuakeAssistController controller;
    std::string line;
    while (std::getline(std::cin, line)) {
        controller.parseAndExecute(line);
    }
    return 0;*/
    // 1. Dosya ismi verilmiş mi kontrol et (PDF Kuralı: Command-line argument)
    if (argc < 2) {
        std::cerr << "Usage: ./QuakeAssist <input_filename>" << std::endl;
        return 1;
    }

    // 2. Dosyayı Aç
    std::ifstream inputFile(argv[1]);
    
    // 3. Dosya açıldı mı kontrol et
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    // 4. Controller'ı başlat
    QuakeAssistController controller;
    std::string line;

    // 5. Dosyadan satır satır oku (cin yerine inputFile kullanıyoruz)
    while (std::getline(inputFile, line)) {
        // Boş satırları atla (Dosya sonundaki boşluklar hata vermesin)
        if (line.empty() || line == "\r") continue;

        // Komutu işlet. Eğer 'CLEAR' gelirse false döner ve çıkarız.
        if (!controller.parseAndExecute(line)) {
            break;
        }
    }

    // 6. Dosyayı kapat
    inputFile.close();

    return 0;
}

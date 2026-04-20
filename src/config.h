/**
 * @file config.h
 * @brief Plik konfiguracyjny z stałymi dla aplikacji PyScript AI Generator
 * @author PyScript AI Generator Team
 * @date 2026-03-25
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

namespace Config {
    /// URL do Ollama API endpoint
    const QString OLLAMA_API_URL = "http://localhost:11434/api/generate";
    
    /// Nazwa modelu do użycia (Bielik lub llama3)
    const QString DEFAULT_MODEL = "llama3";
    
    /// Timeout dla połączeń sieciowych (ms)
    const int NETWORK_TIMEOUT = 60000;
    
    /// System prompt dla generatora kodu Python
    const QString SYSTEM_PROMPT = "You are a Python code generator. Generate only valid Python code without explanations. The code should be ready to execute. Do not include markdown formatting or code blocks (no ```python). Just output pure Python code.";
    
    /// Ścieżka do interpretera Python
    const QString PYTHON_EXECUTABLE = "python";
}

#endif // CONFIG_H

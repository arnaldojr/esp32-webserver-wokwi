# ESP32 Webserver para Wokwi

## Descrição

Este projeto implementa um servidor web simples para o ESP32, projetado para ser executado no simulador Wokwi. O código permite que o ESP32 sirva uma página web básica via Wi-Fi.

## Pré-requisitos

- **Arduino IDE**: Instale a versão mais recente do Arduino IDE (disponível em [arduino.cc](https://www.arduino.cc/en/software)).
- **Placa ESP32**: Certifique-se de que o suporte para ESP32 está instalado no Arduino IDE (via Gerenciador de Placas: ESP32 by Espressif Systems).
- **Wokwi para vscode**: Instale o Wokwi para vscode para executar o projeto localmente direto do vscode.

## Como Executar

### 1. Compilar o Código no Arduino IDE

1. Abra o **Arduino IDE**.
2. Abra o arquivo `esp32-webserver-wokwi.ino` localizado neste repositório.
3. No menu do Arduino IDE, selecione a placa apropriada:
   - Vá em **Ferramentas > Placa > ESP32 Arduino > DOIT ESP32 DEVKIT V1** (ou a placa ESP32 que você possui).
4. Configure a porta serial se necessário (para upload real, mas não é obrigatório para simulação).
5. Clique em **Verificar/Compilar** (ícone de marca de verificação) para compilar o código.
   - Certifique-se de que não há erros de compilação.

### 2. Extrair o Binário Compilado

1. Após a compilação bem-sucedida, no Arduino IDE, vá em **Sketch > Exportar Binário Compilado**.
2. Isso criará uma pasta chamada `build` no diretório do sketch, contendo os arquivos binários compilados (como `.bin`).
   - Esses arquivos são necessários para a execução no Wokwi.

### 3. Executar no Wokwi via Extensão do VS Code

1. Certifique-se de que a extensão **Wokwi for VS Code** está instalada no VS Code (procure por "Wokwi" na aba de extensões).
2. Abra o projeto no **VS Code** (este repositório).
3. Se necessário, ative sua licença do Wokwi: Vá em **View > Command Palette** (ou Ctrl+Shift+P), digite "Wokwi: Activate License" e siga as instruções para obter e inserir a chave de licença.
4. Abra o arquivo `diagram.json` no VS Code.
5. Clique no botão **"Start Simulation"** na extensão Wokwi que aparecerá no editor.
   - Isso iniciará a simulação diretamente no VS Code, carregando o diagrama e o binário compilado da pasta `build`.
6. O servidor web do ESP32 estará rodando na simulação, e você poderá acessar a página web servida pelo dispositivo através da interface do simulador.

### 4. Acessar a Página Web Servida

1. No simulador Wokwi, localize o endereço IP do ESP32 (geralmente exibido no console ou na interface do simulador).
2. Abra um navegador web e digite o endereço IP do ESP32 para acessar a página web servida.
3. Você deve ver a página web básica servida pelo ESP32, confirmando que o servidor web está funcionando corretamente.


## Notas Adicionais

- Para upload real no ESP32 físico: Após compilar, conecte o ESP32 via USB, selecione a porta correta em **Ferramentas > Porta** e clique em **Upload**.
- Certifique-se de que as credenciais de Wi-Fi no código (`ssid` e `password`) estão corretas para o seu ambiente.
- Se houver problemas, verifique os logs no Arduino IDE ou no terminal do Wokwi CLI.

## Estrutura do Projeto

- `esp32-webserver-wokwi.ino`: Código principal do Arduino.
- `wokwi.toml`: Configuração do projeto para Wokwi.
- `diagram.json`: Diagrama do circuito para simulação.
- `build/`: Pasta gerada após compilação, contendo os binários.

Divirta-se explorando o ESP32!
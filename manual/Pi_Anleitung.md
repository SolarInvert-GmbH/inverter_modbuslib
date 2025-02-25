# Pi Anleitung

## Installation

Auf dem Rasperry Pi [https://cloud.cattatech.de/index.php/s/qPpdrr7A8Ak3G4i](https://cloud.cattatech.de/index.php/s/qPpdrr7A8Ak3G4i) im Browser öffen und die neuste `ModbusLib-master-….zip` downloaden. Die gedownloade zip Datei enpacken (rechte Maus hier entpacken).

In der Konsole in den eben enpackten ModbusLib Ordner gehen. zB `cd ~/Downloads/ModbusLib-master/` (hängt vom gewählten Ordner ab)

```sh
pi@raspberrypi:~/Downloads/ModbusLib-master/ $ ./scripts/install_all.sh
```

ausführen

## Node-Red Knoten konfigurieren

 * bei `Command:` `SendRequest` eintragen
 * und Rest ausfüllen

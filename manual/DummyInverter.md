# DummyInverter

Der DummyInverter simuliert SolarInvert Wechselrichter als ein Modbus-Slave-Gerät. Damit kann man die Implementierung von Steuerungen oder Datenvisualisierungen des Wechselrichters, ohne einen realen Wechselrichter, testen.

## Starten

Nach der Installation kann man den DummyInverter starten indem man in der Konsole

```sh
pi@raspberrypi:~ $ Dummy_Inverter

```
eingibt.


Alternativ kann man im File-Manger doppelt auf die `Dummy_Inverter` Anwendung klicken.


## Benutzung

### Connection

Im `Connection` Reiter kann man die serielle Verbindung und die Modbus ID einstellen.

 * Beim `Serail Port` kann die Adresse des seriellen Devices angeben werden.
 * Anschließend drückt man den `Connect` Button.
 * Um eine bestehende Verbindung zu schließen drückt man den `Disconnect` Button.
 * Ganz rechts kann man die Modbus Id einstellen. Der Modbus-Master muss diese ID für die Anfragen benutzen.

![Verbindungsreiter](DummyInverter_Connection.pdf)

### Register

Im Reiter Register werden die SUNSPEC Register simuliert. Es werden alle möglichen SUNSPEC Register mit Registeradresse, Typ, Name und Wert angezeigt.

Für alle Register kann die Aktion des DummyInverters für eine Leseanfrage (`Read Action`) auf dieses Register eingestellt werden.

 * `read` gibt den Wert des Registers zurück, wenn dieser korrekt eingestellt ist (links neben dem Wert ist ein grünes Häkchen).
 * `do nothing` gibt keine Antwort.
 * `exeption1` gibt eine Modbus Exception 1 zurück.
 * `exeption2` gibt eine Modbus Exception 2 zurück.
 * `exeption3` gibt eine Modbus Exception 3 zurück.
 * `exeption4` gibt eine Modbus Exception 4 zurück.

Für Register die geschrieben werden können, gibt es auf der linken Seite noch die Möglichkeit die Aktion bei einer Schreibanfrage einzustellen (`Write Action`).

 * `write` schreibt den Wert des Mobus-Masters und gibt die korrekte Antwort.
 * `do nothing` schreibt nicht und gibt keine Antwort.
 * `exeption1` schreibt nicht und gibt eine Modbus Exception 1 zurück.
 * `exeption2` schreibt nicht und gibt eine Modbus Exception 2 zurück.
 * `exeption3` schreibt nicht und gibt eine Modbus Exception 3 zurück.
 * `exeption4` schreibt nicht und gibt eine Modbus Exception 4 zurück.

![SUNSPEC Register](DummyInverter_Register.pdf)

### FunctionCodes

In den drei FunctionCode-Reitern kann man die SI Modbus Antworten einstellen.

Links steht der Name des FunktionsCodes. Danach kann man die Antwortaktion auswählen.

 * `responde` gibt eine Antwort abhängig von den Werten die rechts stehen. Die Werte müssen korrekt sein (links neben dem Wert ist ein grünes Häkchen).
 * `do nothing` gibt keine Antwort.
 * `exeption1` gibt eine Modbus Exception 1 zurück.
 * `exeption2` gibt eine Modbus Exception 2 zurück.
 * `exeption3` gibt eine Modbus Exception 3 zurück.
 * `exeption4` gibt eine Modbus Exception 4 zurück.

![FunktionsAnfrage](DummyInverter_FunctionCode.pdf)

Hier sehen wir korrekt und falsch eingeben Werte. Bei einem roten Kreuz muss die Eingabe korrigiert werden.

![Invalider eingabe des Werts](DummyInverter_Error.pdf)

## Serielle Verbindung mit der Steuerung

Der DummyInverter implementiert die Slave-Seite der Modbus-Kommunikation. Er ersetzt damit einen realen Wechselrichter. Er muss über eine serielle (UART-) Verbindung mit der Master-Seite der Modbus-Kommuniktion (Steuer/Anzeige-Implementierung) verbunden werden.

### Virtuelle serielle Verbindung

Es ist möglich auf einem PC eine virtuelle serielle Verbindung aufzubauen.

Dazu kann man das Programm `socat` verwenden.

Installation:

```bash
pi@raspberrypi:~ $ sudo apt update
pi@raspberrypi:~ $ sudo apt install socat
```

Aufruf für Device im Systemordner (sudo benötigt):

```bash
pi@raspberrypi:~ $ sudo socat pty,raw,echo=0,perm=0777,link=/dev/ttyS80 \
pty,raw,echo=0,perm=0777,link=/dev/ttyS81
```

Der Befehl öffnet zwei serielle Devices `/dev/ttyS80` und `/dev/ttyS81` (andere Nummern sind möglich. Die Datei sollte noch nicht existieren). Er beendet sich nicht (blockiert). Um ihn zu beenden kann man `Strg+C` (in der entsprechenden Konsole) drücken. Dann verschwinden die beiden seriellen Devices (erst nach durchgeführten test machen).

### Hardware Verbindung

Mit Hilfe von zwei `FDDI`-Adaptern (oder `USB to TTL`-Converter). Dabei muss man die Adapter zwei drei Jumper-Kabeln verbinden.

 * A-GND <-> B-GND
 * A-RX <-> B-TX
 * A-TX <-> B-RX
 * A-USB <-> PC-A
 * B-USB <-> PC-B (kann der selbe sein wie PC-A)

![seriell Hardware-Verbindung](DummyInverter_FDDI.pdf)

# Sprievodca prvým spustením a konfiguráciou EastMesh

Tento dokument slúži ako rýchly sprievodca pre prechod na EastMesh firmware, konfiguráciu Wi-Fi, pripojenie k CLI a prístup k novému dual-broker Web Panelu.

---

## 1. Podporovaný hardvér (Build Targety)
EastMesh je možné skompilovať pre širokú škálu LoRa vývojových dosiek. Najčastejšie prostredia (environments) zahŕňajú:

* **Seeed Studio (Xiao):**
  - `Xiao_S3_WIO_repeater_observer` (a varianty s `_espnow` / `_mqtt_bridge`)
  - `Xiao_C6_repeater_observer`
  - `Xiao_S3_repeater`
  - `Xiao_C3_repeater`
* **Heltec Automation:**
  - `heltec_v4_repeater_observer` / `heltec_v3_repeater_observer` / `Heltec_v2_repeater_observer`
  - `Heltec_Wireless_Tracker_repeater_observer`
  - `Heltec_Wireless_Paper_repeater_observer`
  - `Heltec_WSL3_repeater_observer`
* **LilyGo (T-Beam & T3S3):**
  - `T_Beam_S3_Supreme_SX1262_repeater_observer`
  - `LilyGo_T3S3_sx1262_repeater_observer`
  - `LilyGo_T3S3_sx1276_repeater_observer`
  - `LilyGo_TDeck_repeater_observer`
* **RAK Wireless:**
  - `RAK_4631_repeater`
  - `RAK_3112_repeater_observer`

> [!NOTE]
> Úplný zoznam všetkých prostredí nájdete v súbore `variants/eastmesh/platformio.ini`.

---

## 2. Prvý flash zariadenia
Na zostavenie a nahratie firmvéru sa využíva virtuálne prostredie Pythonu (venv) a PlatformIO.

1. **Aktivujte virtuálne prostredie:**
   ```bash
   source venv/bin/activate
   ```

2. **Kompilácia a nahratie (napr. pre Xiao S3 WIO):**
   ```bash
   pio run -e Xiao_S3_WIO_repeater_observer -t upload --upload-port /dev/tty.usbmodemXXXX
   ```
   *(Nahraďte `/dev/tty.usbmodemXXXX` vaším reálnym sériovým portom).*

3. **Čistý flash (odporúča sa pri problémoch so zavádzačom):**
   Ak sa na sériovom porte objaví chyba `invalid header: 0xffffffff`, je potrebné najprv zmazať flash:
   ```bash
   # Vstúpte do download módu (držte BOOT tlačidlo, stlačte RESET a pustite BOOT)
   pio run -e Xiao_S3_WIO_repeater_observer -t erase
   pio run -e Xiao_S3_WIO_repeater_observer -t upload
   ```

---

## 3. Pripojenie cez USB a konfigurácia Wi-Fi
Po úspešnom flashnutí môžete zariadenie konfigurovať cez sériový monitor:

1. **Spustite monitor portu (rýchlosť 115200 baudov):**
   ```bash
   pio device monitor --port /dev/tty.usbmodemXXXX --baud 115200
   ```

2. **Zadajte Wi-Fi prihlasovacie údaje:**
   Cez CLI príkazový riadok nastavte SSID a heslo pre vašu lokálnu sieť:
   ```cli
   set wifi.ssid MojaDomacaSiet
   set wifi.pwd MojeHesloDoWifi
   ```

3. **Overenie stavu pripojenia:**
   ```cli
   get wifi.status
   ```
   Po chvíli by ste mali vidieť pridelenú IP adresu (napr. `192.168.1.150`).

---

## 4. Pripojenie cez Webové rozhranie (HTTPS)
Zariadenia s prívlastkom `*_repeater_observer` majú v sebe integrovaný zabezpečený HTTPS webový server.

1. Otvorte prehliadač a prejdite na IP adresu zariadenia:
   `https://<IP_ADRESA_ZARIADENIA>/`
2. Prehliadač zobrazí varovanie o certifikáte (zariadenie používa self-signed certifikát). Kliknite na **Pokračovať (Advanced -> Proceed)**.
3. Prihláste sa admin heslom (predvolené heslo je `"password"`, ak nebolo zmenené pri kompilácii cez `-D ADMIN_PASSWORD`).

### Čo nájdete na Web Paneli:
* **MQTT Settings (Dual Custom MQTT):** 
  - Rozhranie obsahuje dve nezávislé sekcie: **MQTT 1** a **MQTT 2**.
  - Pre každý server môžete nezávisle nakonfigurovať `Host:Port`, prenosový protokol (`TCP` alebo secure `WSS`), povoliť TLS šifrovanie a nahrať vlastný **Root CA certifikát** (PEM).
* **CLI Terminal:** 
  - Príkazový riadok priamo v prehliadači pre rýchlu správu zariadenia.
* **Historické štatistiky a grafy (`/stats`):**
  - Sledovanie napätia batérie, voľnej pamäte (heap), LoRa aktivity, šumu a okolitých susedných uzlov (Neighbours).

---

## 5. Rýchle príkazy pre CLI
Zoznam užitočných príkazov pre administráciu:
* `get mqtt.status` — zobrazí stav pripojenia oboch MQTT brokerov.
* `set mqtt.iata KSC` — priradí IATA kód (povinné pre odosielanie MQTT správ).
* `set web off` — vypne webový server po dokončení konfigurácie (ušetrí cennú RAM pre spoľahlivejší chod MQTT brokerov).

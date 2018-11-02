# Tugas Besar 1 Jaringan Komputer
## Sliding Window Protocol

## Petunjuk Penggunaan Program
  Lakukan kompilasi program dengan perintah `make`

  Format eksekusi program sebagai berikut:

  `./sender <filename> <windowsize> <buffersize> <destination_ip> <destination_port>`

  `./receiver <filename> <windowsize> <buffersize> <port>`
  
## Cara Kerja Sliding Window
Pada Sliding Window buatan kami, ada dua file utama, yaitu sender dan receiver.

Sender bertugas untuk membaca file yang mau dikirim, kemudian mengirimkan datanya kepada receiver. Lalu receiver akan menyimpan data ke dalam file external kembali

Pada sender terdapat tiga komponen utama yaitu membaca file dari file eksternal, mengirim frame data, mengirim kembali frame data yang sebelumnya hilang.

Pada receiver terdapat tiga komponen utama yaitu menerima frame data, mengirim ACK, dan mengurus pemindahan data dari frame buffer ke file eksternal.

## Pembagian Tugas
Jansen / 13516011 : Receiver, Sender

Juan Felix Parsaoran / 13516143 : Makefile

Aristoteles Swarna Wirahadi / 13516146 : readme.md

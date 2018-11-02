# Tugas Besar 1 Jaringan Komputer
## Sliding Window Protocol

## Petunjuk Penggunaan Program
  Lakukan kompilasi program dengan perintah `make`

  Format eksekusi program sebagai berikut:

  `./sender <filename> <windowsize> <buffersize> <destination_ip> <destination_port>`

  `./receiver <filename> <windowsize> <buffersize> <port>`
  
## Cara Kerja Sliding Window
Pada Sliding Window buatan kami, ada dua file utama, yaitu sender dan receiver.

Secara garis besar, sender bertugas untuk membaca file yang akan dikirim, kemudian mengirimkan datanya kepada receiver. Lalu receiver akan menyimpan data ke dalam file external kembali.
Sender akan melakukan binding pada hostname dan port tertentu, kemudian dari sisi receiver akan melakukan waiting pada port yang di bind oleh sender. Pada saat port berhasil di bind oleh sisi sender, kemudian akan melakukan pembacaan file yang disimpan pada suatu buffer dengan bentuk binary.

Buffer yang diperoleh kemudian akan dipecah menjadi beberapa frame dengan ukuran maksimum 1024B. Window yang digunakan akan terbatas pada jumlah windowsize yang di input oleh user. Frame tersebut kemudian akan dikirim yang ditandai dengan `SeqNum`. Pada saat frame tersebut telah diterima, akan dilakukan penulisan pada file untuk melakukan konstruksi data yang diterima. Setelah menerima frame, sisi receiver akan mengirim Ack kepada sisi sender untuk menginformasikan bahwa frame dengan `SeqNum` tertentu telah diterima. Apabila tidak ada Ack yang diterima, maka sisi receiver akan mengirim kembali frame dengan ack tersebut.

Sliding Window dibuat dengan protokol `Selective Repeat` yaitu apabila semua frame awal (LRF) sudah di ACK, maka window akan berpindah, sedangkan apabila belum maka akan mengirim lagi. Frame yang dikirim menggunakan checksum yang untuk memastikan apakah file yang dikirim error atau tidak.

Pada sender terdapat tiga komponen utama yaitu membaca file dari file eksternal, mengirim frame data, mengirim kembali frame data yang sebelumnya hilang.
File dibaca dengan menggunakan `ifstream::binary` untuk melakukan penyimpanan data secara biner. Pengiriman kemudian dilakukan berdasarkan format frame yaitu: `[soh][seq_num][data_length][data][checksum]`

Pada receiver terdapat tiga komponen utama yaitu menerima frame data, mengirim ACK, dan mengurus pemindahan data dari frame buffer ke file eksternal.
Frame yang diterima akan dilakukan konstruksi data dengan menggunakan `ofstream::binary`. Pada saat frame sudah diterima, akan dilakukan pengiriman ack yang menandakan bahwa frame dengan seqnum telah di terima.

## Pembagian Tugas
Jansen / 13516011 : Receiver, Sender

Juan Felix Parsaoran / 13516143 : Makefile

Aristoteles Swarna Wirahadi / 13516146 : Readme.md

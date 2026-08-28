# Body Temperature Sensor Validation using DS18B20 & Arduino

## Ringkasan Proyek
Proyek ini merancang dan memvalidasi sistem pengukuran suhu tubuh otomatis menggunakan sensor DS18B20 dan Arduino Uno, dilengkapi sistem alarm untuk mendeteksi suhu di atas ambang normal (indikasi demam). Sistem ini divalidasi terhadap termometer digital sebagai instrumen referensi pada 15 subjek di tiga titik pengukuran berbeda.

## Kenapa DS18B20?
Sensor ini dipilih atas dasar pertimbangan **cost-effectiveness**: harganya jauh lebih terjangkau dan mudah didapat dibanding sensor suhu presisi tinggi lain (misalnya RTD Pt100), menjadikannya pilihan realistis untuk proyek skala kecil/mahasiswa. Proyek ini sekaligus menjadi eksperimen untuk menguji seberapa jauh sensor *low-cost* ini bisa diandalkan untuk aplikasi pengukuran suhu tubuh dibanding alat medis standar — apakah trade-off harga vs akurasi ini sepadan untuk aplikasi non-kritis.

## Alat dan Bahan
- Arduino Uno
- Sensor suhu DS18B20 (waterproof probe)
- LCD 2x16
- Buzzer (indikator alarm)
- Breadboard, kabel jumper, resistor 4700Ω

## Metodologi
1. Sensor DS18B20 dan termometer digital referensi digunakan secara bersamaan pada tiap subjek
2. Pengukuran dilakukan pada 3 titik: sela-sela lengan, lipatan ketiak, dan genggaman tangan
3. Data dibandingkan untuk menghitung selisih dan persentase penyimpangan
4. Alarm otomatis aktif ketika suhu terdeteksi di atas ambang normal (36.1–37.2°C)

## Hasil Utama
- Diuji pada 15 subjek dengan 3 titik pengukuran berbeda
- Selisih pembacaan sensor vs termometer digital: **0.01°C – 0.09°C**
- Persentase penyimpangan: **0.03% – 0.26%** (jauh lebih presisi dari toleransi pabrik ±0.5°C)
- Bias pembacaan konsisten satu arah (sensor selalu sedikit lebih rendah dari termometer digital) di seluruh titik pengukuran
- Sistem alarm berfungsi sesuai rancangan saat mendeteksi suhu di atas normal

## Analisis Sumber Error
Ditemukan pola bias yang **sistematis, bukan acak** — mengindikasikan kombinasi dua faktor:

1. **Response time & kontak termal sensor** — probe DS18B20 memiliki lapisan pelindung waterproof yang tidak dioptimalkan untuk kontak kulit, menyebabkan waktu penyesuaian suhu yang sedikit lebih lambat dibanding termometer digital referensi.
2. **Kondisi lingkungan pengukuran** — eksperimen dilakukan di ruangan ber-AC tanpa penyekat udara di sekitar sensor. Ini didukung temuan riset (Kalashnikov & Elyounsi, 2021) yang menunjukkan pergerakan udara yang tidak dibatasi dapat menyebabkan perbedaan pembacaan signifikan antar sensor suhu digital, bahkan yang ditempatkan berdekatan sekalipun.

Studi yang sama menemukan bahwa setelah faktor pergerakan udara dan perbedaan response time dieliminasi, DS18B20 menunjukkan kesesuaian sangat baik dengan sensor RTD presisi tinggi (Pt100) — mendukung kesimpulan bahwa DS18B20 **akurat secara potensi**, namun performanya sensitif terhadap kondisi pengukuran.

## Kesimpulan
Meski memiliki toleransi akurasi pabrik ±0.5°C, DS18B20 menunjukkan performa aktual yang jauh lebih presisi (error <0.3%) untuk aplikasi pengukuran suhu tubuh non-kritis. Trade-off biaya vs akurasi terbukti sepadan untuk kebutuhan prototipe/edukasi, dengan catatan kondisi pengukuran (isolasi dari aliran udara, waktu stabilisasi cukup) perlu diperhatikan untuk hasil optimal.

## Skill yang Didemonstrasikan
- Akuisisi data sensor & komunikasi protokol 1-Wire
- Validasi instrumen terhadap alat ukur standar (metrologi dasar)
- Analisis statistik: regresi linear, perhitungan error & persentase penyimpangan
- Root cause analysis (membedakan error sistematis vs random)
- Perancangan sistem alarm berbasis ambang batas (threshold-based control)
- Trade-off engineering: mempertimbangkan cost vs performa dalam pemilihan komponen

## Referensi
- Aritonang, W., et al. (2021). *Implementasi Sensor Suhu DS18B20 dan Sensor Tekanan MPX5700AP*. Jurnal Ilmiah Wahana Pendidikan.
- Kalashnikov, A., & Elyounsi, A. (2021). *Evaluating Suitability of a DS18B20 Temperature Sensor for Use in an Accurate Air Temperature Distribution Measurement Network*. MDPI Engineering Proceedings.
- Wulandari, R. (2020). *Rancang Bangun Pengukur Suhu Tubuh Berbasis Arduino Sebagai Alat Deteksi Awal Covid-19*. Prosiding SNFA.

---
*Proyek awal dikembangkan sebagai tugas mata kuliah Eksperimen Fisika, Program Studi Fisika, Universitas Negeri Jakarta (2023).*

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

Analisis kuantitatif lengkap tersedia di [`analysis/sensor_calibration_analysis.ipynb`](analysis/sensor_calibration_analysis.ipynb). Ringkasan temuan utama:

**1. Korelasi sensor vs termometer digital sangat kuat**
Regresi linear di ketiga lokasi menghasilkan **R² = 0.9995–0.9997**, menandakan sensor DS18B20 secara konsisten "mengikuti" nilai referensi dengan sangat baik — bukan pembacaan acak, melainkan bergeser dengan pola yang bisa diprediksi (slope ≈ 0.99–1.00 di semua lokasi).

**2. Bias konsisten satu arah (bukan random)**

| Lokasi | Rata-rata selisih (°C) | Std. deviasi | Rata-rata error (%) |
|---|---|---|---|
| Sela-sela lengan | 0.0647 | 0.0146 | 0.1747% |
| Lipatan ketiak | 0.0633 | 0.0180 | 0.1747% |
| Genggaman tangan | 0.0267 | 0.0105 | 0.0760% |

Standar deviasi yang kecil di setiap lokasi menunjukkan bias-nya stabil, bukan fluktuasi acak — pola ini sejalan dengan penyebab **sistematis**: kombinasi *response time* sensor dan kontak termal probe yang kurang optimal ke kulit (lapisan pelindung waterproof menambah hambatan konduksi panas), diperkuat oleh kondisi ruangan ber-AC tanpa penyekat udara di sekitar sensor saat eksperimen — faktor yang juga didukung literatur (Kalashnikov & Elyounsi, 2021) sebagai penyebab signifikan diskrepansi pembacaan sensor suhu digital.

**3. Koreksi offset berhasil menurunkan error signifikan**

| Lokasi | Offset diterapkan (°C) | Error sebelum | Error sesudah | Penurunan |
|---|---|---|---|---|
| Sela-sela lengan | +0.0647 | 0.1747% | 0.0309% | **−82%** |
| Lipatan ketiak | +0.0633 | 0.1747% | 0.0422% | **−76%** |
| Genggaman tangan | +0.0267 | 0.0760% | 0.0463% | **−39%** |

Setelah diterapkan koreksi offset konstan (rata-rata selisih per lokasi), error turun drastis di semua titik pengukuran — **membuktikan secara kuantitatif** bahwa sumber error memang sistematis dan dapat dikoreksi, bukan murni acak akibat lingkungan.

## Kesimpulan
Meski memiliki toleransi akurasi pabrik ±0.5°C, DS18B20 menunjukkan performa aktual yang jauh lebih presisi (error awal <0.3%, turun hingga <0.05% setelah kalibrasi offset sederhana) untuk aplikasi pengukuran suhu tubuh non-kritis. Trade-off biaya vs akurasi terbukti sepadan untuk kebutuhan prototipe/edukasi — dengan kalibrasi offset sederhana, sensor low-cost ini dapat mencapai akurasi yang mendekati termometer digital, asalkan kondisi pengukuran (isolasi dari aliran udara, waktu stabilisasi cukup) diperhatikan.

## Skill yang Didemonstrasikan
- Akuisisi data sensor & komunikasi protokol 1-Wire
- Validasi instrumen terhadap alat ukur standar (metrologi dasar)
- Analisis statistik: regresi linear (Python/scipy), perhitungan error & persentase penyimpangan
- Kalibrasi instrumen: koreksi offset dan evaluasi hasil kuantitatif
- Root cause analysis (membedakan error sistematis vs random)
- Perancangan sistem alarm berbasis ambang batas (threshold-based control) di Arduino/C
- Trade-off engineering: mempertimbangkan cost vs performa dalam pemilihan komponen

## Struktur Repository
```
├── README.md
├── arduino_code/
│   └── ds18b20_temp_alarm.ino
├── data/
│   ├── raw_temperature_measurements.csv
│   └── sensor_precision_test.csv
├── analysis/
│   └── sensor_calibration_analysis.ipynb
└── images/
    ├── regresi_per_lokasi.png
    └── before_after_koreksi.png
```

## Referensi
- Aritonang, W., et al. (2021). *Implementasi Sensor Suhu DS18B20 dan Sensor Tekanan MPX5700AP*. Jurnal Ilmiah Wahana Pendidikan.
- Kalashnikov, A., & Elyounsi, A. (2021). *Evaluating Suitability of a DS18B20 Temperature Sensor for Use in an Accurate Air Temperature Distribution Measurement Network*. MDPI Engineering Proceedings.
- Wulandari, R. (2020). *Rancang Bangun Pengukur Suhu Tubuh Berbasis Arduino Sebagai Alat Deteksi Awal Covid-19*. Prosiding SNFA.

---
*Proyek awal dikembangkan sebagai tugas mata kuliah Eksperimen Fisika, Program Studi Fisika, Universitas Negeri Jakarta (2023).*

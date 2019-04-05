# SoalShift_Modul3_F16
Kelompok F16 :

Alfin Pradana - 17 - 0191

Hisam Widi Prayoga - 17-0026

Himawan 16 - 0143

<li> Nomor 1
  
Pertama hal yang harus dilakukan adalah menggunakan argv pada function main agak dapat menyimpan inputan sesuai dengan yang dimasukan oleh user. Lalu membuat Thread sesuai dengan banyaknya input yang diberikan, karena diinginkan faktorial secara pararel. lalu array pada argv dimasukan dalam sebuah wadah array lain tetapi dengan bentuk variabel int, dengan menggunakan atol. Setelah dimasukan dalam array bernama store, array tersebut kita sort dari kecil ke besar sesuai dengan permintaan soal (menggunakan bubble sort). Setelah itu buat function bernama factorial, untuk melakukan kalkulasi faktorial. lalu masukan kedalam loop sesuai banyaknya faktorial, setiap thread-threadnya. apabila berhasil artinya mereturn 0. dan gagal jika mereturn selain 0.

<li> Nomor 4
  
Dalam kasus ini kita harus menggunakan mutex agar tidak ada task yang terjadi secara bersamaan. dalam satu waktu hanya boleh dilakukan 1 task. Hal pertama yang diminta untuk dilakukan adalah, mecatat list proses yang sedang berjalan sampai maksimal dengan 10 proses. kita gunakan system pipe dan head atau tail lalu dicatat kedalam folder dan nama file yang di inginkan. lalu setelah itu, hal yang harus dilakukan adalah mengkompres masing-masing file txt lalu setelah berhasil di kompress file yang dikompres atomatis di delete. mMka kita menggunakan zip -m agar setelah di ekstrak file tersebut langung didelete. Setelah itu program diminta untuk memprint "Menunggu 15 Detik Untuk Meng-ekstrak Kembali" dan dan sleep selama 15 detik. setelah itu lanjut ke thread selanjutnya untuk mengekstrak file zip tadi yang telah dibuat di folder masing-masing letak zip tersebut. menggunakan (unzip /direktori/blabla.zip -d /direktori/...) untuk meng ekstrak sesuai dari sumber direktori file, lalu ke file destinasinya.
  
  



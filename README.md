# minitalk
125/100 My Grade

42 okulunun UNIX sinyalleri projesi olan minitalk, iki program arasında UNIX sinyalleri kullanarak iletişim kurmayı amaçlamaktadır.

## 📚 Proje Hakkında

minitalk projesi, bir client ve server programı arasında UNIX sinyallerini (SIGUSR1 ve SIGUSR2) kullanarak string iletişimi sağlamayı hedeflemektedir. Bu proje, işlemler arası iletişim ve sinyal yönetimi konularında deneyim kazandırmayı amaçlar.

## 💻 Teknolojiler

- C Programlama Dili
- UNIX Sinyalleri
- Process ID (PID)
- Bit Manipülasyonu

## 🛠️ Kurulum

### Gereksinimler
- GCC Derleyici
- Make
- UNIX-tabanlı İşletim Sistemi

### Derleme
```bash
make
```

## 📝 Program Kullanımı

### Server
```bash
./server
```

### Client
```bash
./client [server_pid] [mesaj]
```

## 🎯 42 Proje Gereksinimleri

### Zorunlu Kısım
- [x] Server programı
- [x] Client programı
- [x] SIGUSR1 ve SIGUSR2 kullanımı
- [x] Karakter iletimi
- [x] PID doğrulama

### Bonus Kısım
- [x] Unicode karakter desteği
- [x] Sinyal alındı onayı
- [x] Küçük paketler ile hızlı iletişim

## 📚 Kod Örnekleri

### Server
```c
void handle_signal(int signum, siginfo_t *info, void *context)
{
    static int  bit = 0;
    static char c = 0;

    (void)context;
    c |= (signum == SIGUSR1);
    if (++bit == 8)
    {
        ft_putchar_fd(c, 1);
        bit = 0;
        c = 0;
        kill(info->si_pid, SIGUSR1);
    }
    else
    {
        c <<= 1;
        kill(info->si_pid, SIGUSR2);
    }
}

int main(void)
{
    struct sigaction sa;

    ft_printf("Server PID: %d\n", getpid());
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
        pause();
    return (0);
}
```

### Client
```c
void send_char(int pid, char c)
{
    int bit;

    bit = 7;
    while (bit >= 0)
    {
        if (c & (1 << bit))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(100);
        bit--;
    }
}

int main(int argc, char **argv)
{
    int pid;

    if (argc != 3)
    {
        ft_printf("Usage: %s [server_pid] [message]\n", argv[0]);
        return (1);
    }
    pid = ft_atoi(argv[1]);
    while (*argv[2])
        send_char(pid, *argv[2]++);
    return (0);
}
```

## 🔍 Test Senaryoları

### Temel Testler
```bash
# Terminal 1
./server

# Terminal 2
./client $(pgrep server) "Merhaba Dünya!"
```

### Stres Testleri
```bash
# Uzun mesaj testi
./client $(pgrep server) "$(cat uzun_metin.txt)"

# Unicode testi
./client $(pgrep server) "🚀 📚 💻"
```

## 🐛 Hata Ayıklama

### Yaygın Hatalar
1. Sinyal Hataları
   - Kayıp sinyaller
   - Yanlış PID
   - Zamanlama sorunları

2. İletişim Hataları
   - Karakter bozulması
   - Mesaj kaybı
   - Sonsuz döngüler

## 📈 Optimizasyon İpuçları

1. Sinyal Yönetimi
   - Sinyal kuyruklaması
   - Zamanlama ayarları
   - Hata kontrolü

2. Performans
   - Bit manipülasyonu optimizasyonu
   - Bellek kullanımı
   - CPU kullanımı

## 🔒 Güvenlik Kontrolleri

1. PID Doğrulama
   - Geçerli PID kontrolü
   - Erişim izinleri
   - Sinyal yetkileri

2. Veri Güvenliği
   - Buffer kontrolü
   - Sinyal güvenliği
   - Hata yönetimi

## 📝 Lisans

Bu proje [MIT](LICENSE) lisansı altında lisanslanmıştır.

## 📚 Kaynaklar

- [UNIX Signals](https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html)
- [Process Management](https://www.geeksforgeeks.org/process-management-in-linux/)
- [42 Docs](https://harm-smits.github.io/42docs/)

---

⭐️ Bu projeyi beğendiyseniz yıldız vermeyi unutmayın!

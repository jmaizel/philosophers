# 🍝 philosophers

> _"Even philosophers need to eat, but not all at once."_

---

## 🇫🇷 Version Française

### 🎯 Objectif

`philosophers` est une simulation du problème classique des **philosophes mangeurs**. L’objectif est de comprendre les problématiques de **synchronisation**, d’accès concurrent aux ressources, et de gestion fine des **threads**.

Chaque philosophe alterne entre **penser**, **manger**, et **dormir**, en partageant des fourchettes (ressources critiques). Il faut éviter les **deadlocks** et les **conditions de famine**.

---

### 🧱 Fonctionnalités

- Un thread par philosophe  
- Utilisation des **mutex** pour protéger l’accès aux fourchettes  
- Suivi du **temps écoulé**  
- Un philosophe meurt s’il ne mange pas dans les temps  
- Affichage clair des actions : prend une fourchette, mange, dort, pense, meurt  
- Aucune fuite mémoire  

---

### 🛠️ Compilation

```bash
make
```

---

### 🚀 Exécution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

#### Exemple :

```bash
./philo 5 800 200 200
```

→ Lance 5 philosophes avec :
- 800 ms avant de mourir s’ils ne mangent pas
- 200 ms pour manger
- 200 ms pour dormir

---

### ⚠️ Contraintes

- Aucun **deadlock** autorisé  
- Pas d'accès concurrent non synchronisé  
- Affichage lisible, clair et **thread-safe**  

---

### ✨ Bonus (si implémentés)

- Version avec **processus** (au lieu de threads)  
- Sémaphore au lieu de mutex  
- Gestion améliorée du temps ou du logging  
- Affichage couleur ou détaillé  

---

### 📁 Arborescence recommandée

```
philosophers/
├── src/
├── include/
├── Makefile
└── README.md
```

---

### 🧠 Compétences développées

- Programmation **concurrente** en C  
- Utilisation avancée des **pthreads** et des **mutex**  
- Compréhension des problèmes de synchronisation  
- Gestion précise du **temps et des ressources**  
- Écriture de programmes robustes et **thread-safe**

---

## 🇬🇧 English Version

### 🎯 Objective

`philosophers` is a simulation of the classical **Dining Philosophers Problem**, designed to explore **thread synchronization**, **mutex usage**, and **deadlock prevention** in a concurrent environment.

Each philosopher alternates between **thinking**, **eating**, and **sleeping**, and shares forks (critical resources) with their neighbors.

---

### 🧱 Features

- One thread per philosopher  
- Forks protected with **mutexes**  
- Accurate **timing system**  
- A philosopher **dies** if they don’t eat in time  
- Output includes: picking up forks, eating, sleeping, thinking, dying  
- Free of memory leaks and crashes  

---

### 🛠️ Build

```bash
make
```

---

### 🚀 Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

#### Example:

```bash
./philo 5 800 200 200
```

→ Launches 5 philosophers with:
- 800 ms before dying without eating
- 200 ms to eat
- 200 ms to sleep

---

### ⚠️ Constraints

- No **deadlocks**  
- No unsynchronized access to shared resources  
- Clean and readable, **thread-safe output**  

---

### ✨ Bonus (if implemented)

- **Process-based** version instead of threads  
- Use of **semaphores** instead of mutexes  
- Enhanced timing or logging features  
- Graphical or color-enhanced output  

---

### 📁 Suggested Project Structure

```
philosophers/
├── src/
├── include/
├── Makefile
└── README.md
```

---

### 🧠 Skills Gained

- Concurrent programming with **pthreads**  
- Mastering **mutex synchronization**  
- Avoiding **race conditions** and **deadlocks**  
- Managing precise **timing and resource usage**  
- Writing clean, robust, and **thread-safe** C programs

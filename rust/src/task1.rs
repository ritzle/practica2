
mod function;

use function::{theorem_ferma, check_prime_number, log_pow_mod};

use std::io;

fn main() {
    println!("enter baseFirst, enter degreeFirst, enter modFirst");

    let base_first: i32 = read_input();
    let degree_first: i32 = read_input();
    let mod_first: i32 = read_input();

    // Проверка на простоту модуля p
    if !check_prime_number(mod_first) {
        println!("Модуль p должен быть простым числом.");
        return;
    }

    println!("enter baseSecond, enter degreeSecond, enter modSecond");

    let base_second: i32 = read_input();
    let degree_second: i32 = read_input();
    let mod_second: i32 = read_input();

    // Проверка на простоту модуля p
    if !check_prime_number(mod_second) {
        println!("Модуль p должен быть простым числом.");
        return;
    }

    // Проверка на теорему Ферма First
    if theorem_ferma(base_first, degree_first, mod_first) {
        println!("Теорема Ферма выполняется для первого числа.");
    } else {
        println!("Теорема Ферма не выполняется для первого числа.");
    }

    // Проверка на теорему Ферма Second
    if theorem_ferma(base_second, degree_second, mod_second) {
        println!("Теорема Ферма выполняется для второго числа.");
    } else {
        println!("Теорема Ферма не выполняется для второго числа.");
    }

    let result_first_number = log_pow_mod(base_first, degree_first, mod_first);
    let result_second_number = log_pow_mod(base_second, degree_second, mod_second);

    // Выводим результаты и сравниваем их по модулю p
    println!("Результат вычисления a^x mod p: {}", result_first_number);
    println!("Результат вычисления b^y mod p: {}", result_second_number);
    if result_first_number == result_second_number {
        println!("Оба результата совпадают по модулю p.");
    } else {
        println!("Результаты по модулю p не совпадают.");
    }
}

fn read_input() -> i32 {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    input.trim().parse().expect("Please enter a number")
}




mod function;

use function::extended_alg_euclid;

use std::io;

fn main(){

    println!("Введите число: ");
    let mut number = String::new();
    io::stdin().read_line(&mut number).expect("Не удалось прочитать строку");
    let number: i32 = number.trim().parse().expect("Ожидалось целое число");

    println!("Введите mod: ");
    let mut mod_input = String::new();
    io::stdin().read_line(&mut mod_input).expect("Не удалось прочитать строку");
    let mod_input: i32 = mod_input.trim().parse().expect("Ожидалось целое число");

    let mod_inverse = extended_alg_euclid(number, mod_input);
    println!("Обратное число к числу {} по mod {} = {}", number, mod_input, mod_inverse);
}





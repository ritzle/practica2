//use std::vec::Vec;
use std::io;

pub fn theorem_ferma(number: i32, degree: i32, modulo: i32) -> bool {
    if check_prime_number(modulo) && (number % degree != 0) && degree == modulo - 1 {
        return true;
    }
    false
}

pub fn check_prime_number(n: i32) -> bool {
    for i in 2..=(n as f64).sqrt() as i32 {
        if n % i == 0 {
            return false;
        }
    }
    true
}

pub fn log_pow_mod(number: i32, degree: i32, modulo: i32) -> i64 {
    let mut result: i64 = 1;
    let mut mult: i64 = number as i64;

    let mut binary_number: Vec<i32> = Vec::new();
    to_binary(degree, &mut binary_number);

    for &bit in binary_number.iter().rev() {
        if bit != 0 {
            result = (result * mult) % (modulo as i64);
        }
        mult = (mult * mult) % (modulo as i64);
    }
    result
}

pub fn to_binary(degree: i32, binary_num: &mut Vec<i32>) {
    let mut degree = degree;
    while degree > 0 {
        binary_num.push(degree % 2);
        degree /= 2;
    }
    binary_num.reverse();
}

pub fn extended_alg_euclid(c: i32, m: i32) -> i32 {
    let mut table: Vec<Vec<i32>> = Vec::new();
    let first_row = vec![c, 1, 0, 0];
    let second_row = vec![m, 0, 1, 0];
    table.push(first_row);
    table.push(second_row);

    loop {
        let prev_row = &table[table.len() - 2];
        let curr_row = &table[table.len() - 1];

        let r = prev_row[0] % curr_row[0];
        let q = prev_row[0] / curr_row[0];
        let x = prev_row[1] - q * curr_row[1];
        let y = prev_row[2] - q * curr_row[2];

        if r == 0 {
            let last_row = vec![r, x, y, 0];
            table.push(last_row);
            break;
        }

        let new_row = vec![r, x, y, q];
        table.push(new_row);
    }

    println!("r   x   y  q");
    for row in &table {
        println!("{:?}", row);
    }
    println!("");

    let inverse = &table[table.len() - 2];
    inverse[1] + m
}

pub fn data_input(base: &mut i32, prime: &mut i32, alisa_degree: &mut i32, bob_degree: &mut i32) -> bool {
    println!("enter general base: ");
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    *base = input.trim().parse().expect("Please enter a number");

    println!("enter prime number: ");
    input.clear();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    *prime = input.trim().parse().expect("Please enter a number");

    if !check_prime_number(*prime) {
        println!("простое число должно быть простым числом.");
        return false;
    }

    if *prime < 211 {
        println!("возьмите число больше (223).");
        return false;
    }

    println!("Alisa enter degree: ");
    input.clear();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    *alisa_degree = input.trim().parse().expect("Please enter a number");

    println!("Bob enter degree: ");
    input.clear();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    *bob_degree = input.trim().parse().expect("Please enter a number");

    true
}

pub fn encrypt(plain_text: &str, secret_alisa_key: i64, modulo: i32) -> Vec<i32> {
    let mut encrypted_characters: Vec<i32> = Vec::new();

    for ch in plain_text.chars() {
        let number_ascii = ch as i32;
        let c2_val = (number_ascii * (secret_alisa_key as i32)) % modulo;
        encrypted_characters.push(c2_val);
    }

    encrypted_characters
}

pub fn decrypt(ciphertext: &Vec<i32>, secret_bob_key: i32, modulo: i32) -> String {
    let mut decrypted_text = String::new();

    let s_inverse = mod_inverse(secret_bob_key, modulo);

    for &enc_char in ciphertext {
        let number_ascii = (enc_char * s_inverse as i32) % modulo;
        decrypted_text.push(std::char::from_u32(number_ascii as u32).unwrap());
    }

    decrypted_text
}

pub fn mod_inverse(a: i32, m: i32) -> i64 {
    let m0 = m;
    let mut y = 0;
    let mut x = 1;

    if m == 1 {
        return 0;
    }

    let mut a = a as i32;
    let mut m = m as i32;

    while a > 1 {

        let q = a / m;
        let t = m;
        m = a % m;
        a = t;
        let t = y;
        y = x - q * y;
        x = t;
    }

    if x < 0 {
        x += m0 as i32;
    }

    x as i64
}

pub fn fast_pow_mod(number: i32, degree: i32, modulo: i32) -> i64 {
    if degree == 0 {
        return 1;
    }

    let result = fast_pow_mod(number % modulo, degree / 2, modulo) as i64;
    let result_squared = (result * result) % (modulo as i64);

    if degree % 2 == 0 {
        result_squared
    } else {
        (((number % modulo) as i64 * result_squared) % (modulo as i64)) as i64
    }
}

pub fn secret_keys(base: i32, alisa_degree: i32, bob_degree: i32, modulus: i32) -> (i64, i64) {
    let secret_alisa_key = fast_pow_mod(base, alisa_degree, modulus);
    let y_mod = fast_pow_mod(base, bob_degree, modulus);
    let x_mod = fast_pow_mod(y_mod as i32, alisa_degree, modulus);
    let z = mod_inverse(bob_degree, modulus - 1); //должны быть взаимно простые 
    let secret_bob_key = fast_pow_mod(x_mod as i32, z as i32, modulus);

    (secret_alisa_key, secret_bob_key)
}
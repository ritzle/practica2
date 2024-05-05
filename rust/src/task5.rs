mod function;

use function::{fast_pow_mod};

use std::io;

fn main() {
    println!("base: ");
    let mut base = String::new();
    io::stdin().read_line(&mut base).expect("Failed to read line");
    let base: i32 = base.trim().parse().expect("Please enter a number");

    println!("degree: ");
    let mut degree = String::new();
    io::stdin().read_line(&mut degree).expect("Failed to read line");
    let degree: i32 = degree.trim().parse().expect("Please enter a number");

    println!("degree degree: ");
    let mut degree_degree = String::new();
    io::stdin().read_line(&mut degree_degree).expect("Failed to read line");
    let degree_degree: i32 = degree_degree.trim().parse().expect("Please enter a number");

    println!();

    //
    /*на примере (3^7) ^ 8
        сначала n =  3^7mod 10
        потом считаем n^8 mod m
    */

    let last_digit_number = fast_pow_mod(base, fast_pow_mod(degree, degree_degree, 10) as i32, 10); // for the last digit
    println!("последнее число: {}", last_digit_number);

    println!();
}

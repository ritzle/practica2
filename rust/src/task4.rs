mod function;

use function::{data_input, fast_pow_mod, secret_keys, encrypt, decrypt};

use std::io;

use std::fs::File;
use std::io::{BufReader,BufWriter,BufRead, Write};
use std::vec::Vec;
use std::io::Error;


// Алиса отправляет сообщение бобу
fn main(){

    let mut base: i32 = -1; 
    let mut mod_input: i32 = -1; 
    let mut alisa_degree : i32= -1; 
    let mut bob_degree: i32 = -1;

    if data_input(&mut base, &mut mod_input, &mut alisa_degree, &mut bob_degree){
        println!("{} {} {} {}", base, mod_input, alisa_degree, bob_degree);

        let (secret_alisa_key, secret_bob_key) = secret_keys(base, alisa_degree, bob_degree, mod_input);
        println!("Secret Alisa Key: {}", secret_alisa_key);
        println!("Secret Bob Key: {}", secret_bob_key);

        encrypt_the_message(secret_alisa_key, mod_input);
        decrypt_the_message(secret_bob_key, mod_input);

    }

}

fn from_string_to_vector(input: &str) -> Vec<i32> {
    let numbers: Vec<i32> = input.split_whitespace()
                                .map(|x| x.parse().unwrap())
                                .collect();
    numbers
}

fn encrypt_the_message(secret_alisa_key: i64, modulus: i32) -> Result<(), Error> {
    let file_message = File::open("messages.txt")?;
    let file_encrypted = File::create("encryptedMessage.txt")?;

    let reader = BufReader::new(file_message);
    let mut writer = BufWriter::new(file_encrypted);

    for line in reader.lines() {
        let message = line?;
        let cipher_text = encrypt(&message, secret_alisa_key, modulus);

        for num in cipher_text {
            write!(writer, "{} ", num)?;
        }
        writeln!(writer)?;
    }

    Ok(())
}

fn decrypt_the_message(secret_bob_key: i64, modulus: i32) -> Result<(), Error> {
    let file_encrypted = File::open("encryptedMessage.txt")?;
    let file_decrypted = File::create("decryptedMessage.txt")?;

    let reader = BufReader::new(file_encrypted);
    let mut writer = BufWriter::new(file_decrypted);

    for line in reader.lines() {
        let encrypted_line = line?;
        let vec_message = from_string_to_vector(&encrypted_line);

        let decrypted_text = decrypt(&vec_message, secret_bob_key as i32, modulus);

        write!(writer, "{} ", decrypted_text)?;
        writeln!(writer)?;
    }

    Ok(())
}


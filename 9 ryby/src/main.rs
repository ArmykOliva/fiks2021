use std::io;
use std::vec::Vec;

fn main() {
    //read input
    let mut line = String::new();
    io::stdin().read_line(&mut line).unwrap();
    let split = line.split_whitespace();
    let vec: Vec<&str> = split.collect();

    //parse input
    let N: u16 = vec[0].parse().unwrap();
    let sx: i16 = vec[1].parse().unwrap();
    let sy: i16 = vec[2].parse().unwrap();

    for i in 0..N {
        line = "".to_string();
        io::stdin().read_line( &mut line).unwrap();
        let split = line.split_whitespace();
        for (j,coordinate) in split.enumerate() {
            if (j == 0) {continue; }
            print!("{}",coordinate);
        }
    }
}

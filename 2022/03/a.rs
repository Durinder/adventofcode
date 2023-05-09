use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() {
    let mut common = String::new();
    if let Ok(lines) = read_lines("./input.txt") {
        for line in lines {
            if let Ok(items) = line {
                let length = items.chars().count();
                let first = &items[..length / 2];
                let second = &items[length / 2..length];
                for i in first.chars() {
                    if second.contains(i) {
                        common.push_str(&i.to_string());
                        break;
                    } 
                }
            }
        }
    }
    let all = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    let mut res = 0;
    let mut count = 1;
    for i in all.chars() {
        for j in common.chars() {
            if i == j {
                res += count;
                println!("{} {} {}", count, i, j);
            }
       }
       count += 1;
    }
    println!("{}", res);
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
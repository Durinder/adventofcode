use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() {
    let mut common = String::new();
    let mut one = String::new();
    let mut two = String::new();
    let mut three = String::new();
    if let Ok(lines) = read_lines("./input.txt") {
        let mut counter = 0;
        for line in lines {
            if let Ok(items) = line {
                counter += 1;
                if counter % 3 == 1 {
                    one = items;
                } else if counter % 3 == 2 {
                    two = items;
                } else {
                    three = items;
                    for i in one.chars() {
                        if two.contains(i) && three.contains(i) {
                            common.push_str(&i.to_string());
                            break;
                        }
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
            }
       }
       count += 1;
    }
    println!("{}, {}", res, common);
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

struct Section {
    start: u16,
    end: u16,
}

fn get_number(s: String, first: bool) -> Option<u16>
{
    if first {
        s.find('-').map(|i| s[..i].parse().ok()).flatten()
    }
    else {
        s.find('-').map(|i| s[i+1..].parse().ok()).flatten()
    }
}

fn main() {
    let mut contains = 0;
    if let Ok(lines) = read_lines("./input.txt") {
        for line in lines {
            if let Ok(sections) = line {
                let v: Vec<&str> = sections.split(",").collect();
                let first = Section {
                    start: get_number(v[0].to_string(), true),
                    end: get_number(v[0].to_string(), false),
                };
                let second = v[1].to_string();
                
                println!("{}", first);
            }
        }
    }
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
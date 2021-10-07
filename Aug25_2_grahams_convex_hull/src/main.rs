use std::cmp::Ordering;

fn main() {
    let mut points: Vec<Point> = vec![
        Point::new(0, 10),
        Point::new(1, 18),
        Point::new(2, 14),
        Point::new(4, 2),
        Point::new(5, 9),
        Point::new(6, 13),
        Point::new(7, 7),
        Point::new(8, 17),
        Point::new(9, 4),
        Point::new(15, 11),
    ];

    let starting_point = get_starting_point(&points);
    let initial_vector = Vector::new(0, -10);

    sort_by_lexicographic_polar_sorted_order(&mut points, &starting_point, &initial_vector);

    //This is the part where the convex hull problem is solved completely using angles

    let mut convex_hull_stack: Vec<&Point> = Vec::new();

    convex_hull_stack.push(&points[0]);
    convex_hull_stack.push(&points[1]);
    convex_hull_stack.push(&points[2]);

    for i in 3..points.len() {
        loop {
            let point = &points[i];
            let top_point = convex_hull_stack.pop().unwrap();
            let top_point2 = *convex_hull_stack.last().unwrap();

            let new_vec = point.get_relative_position(top_point2);
            let prev_vec = top_point.get_relative_position(top_point2);

            let resultant_angle = Vector::resultant_of(&new_vec, &prev_vec).angle_between(&prev_vec);

            if resultant_angle > 0 as f64 {
                convex_hull_stack.push(top_point);
                convex_hull_stack.push(point);
                break;
            }
        }
    }



    for &point in &convex_hull_stack {
        point.print();
    }
}

fn get_starting_point(points: &Vec<Point>) -> Point {
    let mut starting_point: &Point = &points[0];
    for point in points {
        if point.x < starting_point.x {
            starting_point = point;
        }
        else if point.x == starting_point.x {
            if point.y < starting_point.y {
                starting_point = point
            }
        }
    }

    Point::new(starting_point.x, starting_point.y)
}

fn sort_by_lexicographic_polar_sorted_order(points: &mut Vec<Point>, starting_point: &Point, initial_vector: &Vector) {
    points.sort_by(|a, b| {
        let a_angle = a.get_relative_position(starting_point).angle_between(initial_vector);
        let b_angle = b.get_relative_position(starting_point).angle_between(initial_vector);
        if a_angle < b_angle {
            Ordering::Less
        }
        else if a_angle > b_angle {
            Ordering::Greater
        }
        else {
            Ordering::Equal
        }
    });
}



struct Point {
    x: i32,
    y: i32,
}

impl Point {
    fn new(x: i32, y: i32) -> Point {
        Point { x, y }
    }

    fn print(&self) {
        println!("x: {}, y: {}", self.x, self.y);
    }

    fn distance_from(&self, other: &Point) -> f64 {
        let x_diff = self.x - other.x;
        let y_diff = self.y - other.y;
        ((x_diff * x_diff + y_diff * y_diff) as f64).sqrt()
    }

    fn get_relative_position(&self, with_respect_to_point: &Point) -> Vector {
        let x_diff = self.x - with_respect_to_point.x;
        let y_diff = self.y - with_respect_to_point.y;
        Vector::new(x_diff, y_diff)
    }
}



struct Vector {
    x: i32,
    y: i32,
}

impl Vector {
    fn new(x: i32, y: i32) -> Vector {
        Vector { x, y }
    }

    fn print(&self) {
        println!("{}i + {}j", self.x, self.y);
    }

    fn magnitude(&self) -> f64 {
        ((self.x * self.x + self.y * self.y) as f64).sqrt()
    }

    fn dot_product(&self, other: &Vector) -> i32 {
        self.x * other.x + self.y * other.y
    }

    fn cross_product(&self, other: &Vector) -> i32 {
        self.x * other.y - self.y * other.x
    }

    fn angle_between(&self, other: &Vector) -> f64 {
        let cross_product = self.cross_product(other) as f64;
        let dot_product = self.dot_product(other) as f64;
        //TODO: The negative sign is used to correct for some other mistake I made elsewhere (in terms of dot or cross product)
        -cross_product.atan2(dot_product)
    }

    fn resultant_of(vec1: &Vector, vec2: &Vector) -> Vector {
        let x_diff = vec1.x + vec2.x;
        let y_diff = vec1.y + vec2.y;
        Vector::new(x_diff, y_diff)
    }
}


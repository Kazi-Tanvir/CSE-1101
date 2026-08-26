#include <stdio.h>

// Discount Calculation Function
float discountTK(float price)
{
    float discount = 0;

    if (price >= 5000)
    {
        discount = price * 0.1;
        if (discount >= 2000)
        {
            discount = 2000;
        }
    }
    else if (price == 2027)
    {
        discount = 270;
    }
    else if (price >= 3000 && price <= 4000)
    {
        discount = price * 0.05;
    }
    else if (price >= 500)
    {
        discount = 50;
    }

    return discount;
}

int main()
{
    float budget, points, real_price;
    float total_spent = 0, total_discount_earned = 0;
    int item_count = 0;

    // 1. Initial Inputs
    printf("Enter your initial budget: ");
    scanf("%f", &budget);
    printf("Enter your initial points: ");
    scanf("%f", &points);

    printf("\n--- Shopping Started ---\n");

    // 2. Loop runs as long as budget is greater than 0
    while (budget > 0)
    {
        printf("\nEnter product %d price (or 0 to checkout): ", item_count + 1);
        scanf("%f", &real_price);

        // Break loop if user wants to stop shopping
        if (real_price == 0)
        {
            break;
        }

        // 3. Cycle Calculations
        float point_tk = points / 40.0;
        float discount = discountTK(real_price);
        float pay = real_price - discount - point_tk;
        float new_points = 0;

        if (pay < 0)
        {
            pay = 0;
            // Calculate leftover points that weren't needed to cover the price
            float unused_point_tk = -(real_price - discount - point_tk);
            new_points = unused_point_tk * 40.0;
        }
        else
        {
            new_points = 0;
        }

        // Add the new points earned from this cycle
        new_points = new_points + (0.4 * real_price);
        
        // 4. Update core variables for the next loop
        points = new_points;
        budget -= pay;
        
        // Track summary stats
        total_spent += pay;
        total_discount_earned += (real_price - pay); // Tracks total money saved via discounts + points
        item_count++;

        // 5. Output after each cycle
        printf("-> Payable amount: %.2f\n", pay);
        printf("-> Remaining Budget: %.2f\n", budget);
        printf("-> Current Points: %.2f\n", points);

        if (budget <= 0)
        {
            printf("\n[!] Notice: You have run out of budget!\n");
        }
    }

    // 6. Overall Summary
    printf("\n=== Overall Summary ===\n");
    printf("Total Items Bought: %d\n", item_count);
    printf("Total Amount Spent: %.2f Taka\n", total_spent);
    printf("Total Value Saved (Discount + Points used): %.2f Taka\n", total_discount_earned);
    printf("Final Remaining Budget: %.2f Taka\n", budget);
    printf("Final Points Balance: %.2f Points\n", points);

    return 0;
}
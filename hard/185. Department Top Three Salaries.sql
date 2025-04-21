SELECT
    Department,
    Employee,
    Salary
FROM (
    -- Subquery to rank employees by salary within each department
    SELECT
        d.name AS Department,           -- Department name from Department table
        e.name AS Employee,            -- Employee name from Employee table
        e.salary AS Salary,             -- Employee salary
        DENSE_RANK() OVER (             -- Window function to assign ranks
            PARTITION BY e.departmentId -- Group by department
            ORDER BY e.salary DESC      -- Order by salary descending
        ) AS rnk                        -- Rank column alias
    FROM
        Employee e                      -- From Employee table (aliased as e)
        JOIN Department d              -- Joined with Department table (aliased as d)
        ON e.departmentId = d.id        -- Join condition: department ID matches
)
-- Filter to only include top 3 ranked salaries in each department
WHERE
    rnk <= 3;

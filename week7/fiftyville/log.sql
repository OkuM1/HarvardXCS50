-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema --copy schema to table.txt
SELECT * FROM crime_scene_reports;

.tables

SELECT description
     FROM crime_scene_reports
    WHERE month = 7 AND day = 28
    AND street = "Humphrey Street";
-- theft happened at 10:15 that day, 3 witnesses mention bakery. littering

SELECT * FROM bakery_security_logs
        WHERE month = 7 AND day = 28
        AND hour < 11;
-- 2 id enter the bakery at 10:08 at and 10:14 before theft shortly after many exit
--  258 | 2021 | 7     | 28  | 10   | 8      | entrance | R3G7486
--  259 | 2021 | 7     | 28  | 10   | 14     | entrance | 13FNH73

SELECT *
    FROM people
    WHERE license_plate = "13FNH73";

-- 325548 | Brandon | (771) 555-6667 | 7874488539      | R3G7486
-- 745650 | Sophia | (027) 555-1068 | 3642612721      | 13FNH73
-- sophia transcript no meaningful insight for case. new approach necessary

SELECT transcript, name
    FROM interviews
    WHERE month = 7 AND day = 28;
-- Ruth: thief withdrew money before bakery at leggett street, Eugene: thief called when left bakery for < 1min and take early flight from fiftville
-- other person shall buy flight ticket for him, eugene also mentions a german accent and thief might be unsure of adress

SELECT * FROM atm_transactions
    WHERE month = 7 AND day = 28
    AND atm_location = "Leggett Street";

-- many withdrawals on that at legett street. doesnt help. check if any germans withdrew money ?

SELECT *
    FROM airports
        JOIN flights ON airports.id = flights.origin_airport_id
 WHERE month = 7 AND day = 28
    ORDER BY hour;
-- closest flight to 10:15 from Fiftyville took place on 13:49
-- flight id 6

SELECT passport_number
    FROM passengers
        JOIN flights ON flights.id = passengers.flight_id
    WHERE flight_id = 6 AND month = 7 AND day = 28;
-- passport numbers of people who took that flight

SELECT *
    FROM people
    WHERE passport_number =
    (SELECT passport_number
    FROM passengers
        JOIN flights ON flights.id = passengers.flight_id
    WHERE flight_id = 6)
    ;

-- match passports with people. match found
-- 780088 | Nicole | (123) 555-5144 | 3835860232      | 91S1K32
-- return to witnesses new approach

SELECT transcript, name
    FROM interviews
    WHERE month = 7 AND day = 28;

-- Eugene, Barbara, Ruth

-- check license plate after theft < 11min

SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7 AND day = 28
    AND hour = 10 AND minute > 15 AND minute < 25;
-- all possible suspect license plates
-- now check people who withdrew at atm

SELECT account_number, amount
  FROM atm_transactions
  WHERE year = 2021
   AND month = 7
   AND day = 28
   AND atm_location = 'Leggett Street'
   AND transaction_type = 'withdraw';

-- account numbers available now

SELECT name
    FROM atm_transactions
    JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
    JOIN people ON people.id = bank_accounts.person_id
        WHERE year = 2021 AND month = 7 AND day = 28
        AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw"
    ;
-- names on the withdrawal time and license plates leaving the bakery security logs

SELECT name
    FROM people
    JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
    WHERE month = 7 AND day = 28
    AND hour = 10 AND minute > 15 AND minute < 25;
-- check license plates against people name seperately
-- names

-- check phone calls after theft time
-- names on callers
SELECT name, caller, receiver
    FROM phone_calls
    JOIN people ON people.phone_number = phone_calls.caller
    WHERE month = 7 AND day = 28
    AND duration < 60;

-- check all flights again from fiftyville: ID 8
-- reread flight for suspect is supposed to be on 29 not 28
SELECT full_name, flights.id, city, flights.hour, flights.minute
  FROM airports
  JOIN flights ON airports.id = flights.destination_airport_id
 WHERE flights.origin_airport_id =
       (SELECT id
            FROM airports
            WHERE city = "Fiftyville")
         AND flights.month = 7 AND flights.day = 29
         ORDER BY flights.hour, flights.minute;

-- next flight is to LaGuardia Airport in New York City ID 36

SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
  FROM people
  JOIN passengers ON people.passport_number = passengers.passport_number
  JOIN flights ON passengers.flight_id = flights.id
    WHERE flights.id = 36
        ORDER BY passengers.passport_number;

-- calling all lists of names. callers, flight passengers to laguardia and license_plate holders as well as atm withdrawers
-- crossreferencing names. bruce is in all lists. calls receiver number -might be accomplice
-- checking for accomplice

SELECT name
    FROM people
    WHERE phone_number = "(375) 555-8161";

-- name is Robin. must be accomplice
-- case closed
# SSC Result Fetcher (`ssres`)

A C-based command-line tool designed to fetch and organize Secondary School Certificate (SSC) results from the Board of Intermediate and Secondary Education, Chittagong (BISE-CTG) official website.

## Overview

`ssres` automates the retrieval of academic results for a range of roll numbers. It handles network communication, parses HTML responses, stores data in a structured SQLite database, and generates formatted HTML reports.

## Features

- **Automated Data Gathering**: Efficiently fetches results for a specified range of roll numbers.
- **SQLite Database Integration**: Stores results in `sscResult.db` for persistent access and advanced querying.
- **Flexible Sorting**: Order results by Total Marks (with/without CA), GPA, Name, or Roll Number.
- **HTML Reporting**: Generates a professional HTML table for easy visualization of results.
- **Incremental Fetching**: Automatically skips already downloaded results to save time and bandwidth.
- **Robust Network Handling**: Includes timeout management and retry logic for server interactions.

## Prerequisites

- **GCC**: GNU Compiler Collection.
- **SQLite3 Development Library**: `libsqlite3-dev` (on Linux) or equivalent.
- **Make**: Build automation tool.

## Installation

To build the project, run:

```bash
make
```

This will produce the `ssres` executable.

## Usage

```bash
./ssres -f <from_roll> -t <to_roll> [options]
```

### Basic Examples

**Fetch results for a range and generate default report:**
```bash
./ssres -f 100001 -t 100500
```

**Sort existing data by GPA in ascending order and output to a custom file:**
```bash
./ssres -s -2 -r -o my_results.html
```

### Options

| Option | Description |
| :--- | :--- |
| `-f <roll>` | Starting roll number. |
| `-t <roll>` | Ending roll number. |
| `-o <file>` | Path for the output HTML file (default: `/sdcard/result.html`). |
| `-s` | Sort only; do not attempt to download new data. |
| `-r` | Reverse sort (use ascending order instead of descending). |
| `-0` | Sort by total number without CA (default). |
| `-1` | Sort by total number (including CA). |
| `-2` | Sort by GPA. |
| `-3` | Sort by Name. |
| `-4` | Sort by Roll Number. |

## Project Structure

- `main.c`: Entry point and command-line interface logic.
- `ssres.h`: Core data structures and function prototypes.
- `dataGatherer.c`: Orchestrates the fetching process and database lifecycle.
- `getData.c`: Manages low-level socket communication and HTTP protocol handling.
- `handleData.c`: Parses server responses and maps them to the internal data model.
- `giveResult.c`: Queries the database and formats the final HTML output.
- `checkAvailable.c`: Checks for existing database records to prevent duplicates.
- `itoa.c`: Utility for integer-to-string conversion.

## Database Schema

The application stores data in a `SCIENCE` table within `sscResult.db`. Fields include:
- Personal Info: Name, Roll No, Board, Father's/Mother's Name, Group, etc.
- Academic Info: GPA, Institution, Session, Registration No.
- Subject Marks: Bangla, English, Math, Physics, Chemistry, Biology, ICT, etc.
- Totals: Total marks with and without Continuous Assessment (CA).

---
*Note: This tool is specifically tailored for the BISE-CTG result server format.*

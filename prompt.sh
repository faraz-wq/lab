#!/bin/bash

# Set your Gemini API key
API_KEY="AIzaSyAmGYwh-kyGHJo_X-x6OaGo4ryuW28P4wE"

# Gemini endpoint
ENDPOINT="https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=$API_KEY"

# Ask the user for a query
read -p "Enter your query: " USER_QUERY

# Build the JSON payload
JSON_PAYLOAD=$(jq -n --arg query "$USER_QUERY" '{
  contents: [{
    parts: [{ text: $query }]
  }]
}')

# Send the curl request
RESPONSE=$(curl -s -X POST "$ENDPOINT" \
  -H "Content-Type: application/json" \
  -d "$JSON_PAYLOAD")

# Extract and clean the output
CLEANED_OUTPUT=$(echo "$RESPONSE" | jq -r '.candidates[0].content.parts[0].text')

# Display the cleaned output
echo
echo "=== Gemini Response ==="
echo "$CLEANED_OUTPUT"

echo

# Create a safe filename
DATETIME=$(date +"%Y%m%d_%H%M%S")
SHORT_OUTPUT=$(echo "$CLEANED_OUTPUT" | head -c 30 | tr -dc '[:alnum:]')
FILENAME="${DATETIME}_${SHORT_OUTPUT}.html"

# Generate HTML content
cat <<EOF > "$FILENAME"
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Gemini Response - $DATETIME</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; background: #f9f9f9; color: #333; }
        .container { background: #fff; padding: 20px; border-radius: 8px; box-shadow: 0 2px 8px rgba(0,0,0,0.1); }
        h1 { font-size: 24px; }
        pre { background: #f4f4f4; padding: 15px; border-radius: 5px; }
    </style>
</head>
<body>
    <div class="container">
        <h1>Gemini Response</h1>
        <pre>$(echo "$CLEANED_OUTPUT" | sed 's/&/\&amp;/g; s/</\&lt;/g; s/>/\&gt;/g')</pre>
    </div>
</body>
</html>
EOF

echo "Saved to: $FILENAME"
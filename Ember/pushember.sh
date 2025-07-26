#!/bin/bash

# Usage: ./push.sh [commit_message]

EXPECTED_REPO="https://github.com/Shagedoorn1/Ember.git"
FILES="Emberfile README.md Makefile include/ src/ examples/ test.sh"

# Optional: extract version from a tag file later
COMMIT_MSG=${1:-"🔥 Update Ember build tool"}

# Check if inside a Git repo
if ! git rev-parse --is-inside-work-tree > /dev/null 2>&1; then
    echo "⚠️  Not inside a git repository. Initializing..."
    git init
fi

# Check current remote URL
REMOTE_URL=$(git config --get remote.origin.url)

if [[ "$REMOTE_URL" != "$EXPECTED_REPO" ]]; then
    echo "⚠️  Remote origin mismatch:"
    echo "     Found:    $REMOTE_URL"
    echo "     Expected: $EXPECTED_REPO"
    echo "🔁 Updating remote origin..."
    git remote remove origin 2>/dev/null
    git remote add origin "$EXPECTED_REPO"
fi

# Add, commit, push
echo "📦 Adding files..."
git add .

echo "📜 Committing with message: $COMMIT_MSG"
git commit -m "$COMMIT_MSG"

echo "⬇️ Pulling latest changes from origin/main..."
git pull --rebase origin main

echo "⬆️ Pushing to origin/main..."
git branch -M main
git push -u origin main

echo "✅ Ember push complete!"

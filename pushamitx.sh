#!/bin/bash

# Usage: ./pushamitx.sh [commit_message]

FILE=AmitX/amitx_info.h

if [[ ! -f $FILE ]]; then
    echo "Error: $FILE not found!"
    exit 1
fi

VERSION=$(grep AMITX_VERSION $FILE | sed -E 's/.*"([^"]+)".*/\1/')
OVERSION=$(grep OWLY_VERSION $FILE | sed -E 's/.*"([^"]+)".*/\1/')

if [[ -z "$VERSION" ]]; then
    echo "Error: could not extract AmitX version number from $FILE"
    exit 1
fi

if [[ -z "$OVERSION" ]]; then
    echo "Error: could not extract Owly version number from $FILE"
    exit 1
fi

COMMIT_MSG=${1:-"Update on: Amitx version $VERSION; Owly version $OVERSION"}

if ! git rev-parse --is-inside-work-tree > /dev/null 2>&1; then
    echo "Initializing git repository..."
    git init
fi

git add AmitX README.md pushamitx.sh
git commit -m "$COMMIT_MSG"

if git remote | grep origin > /dev/null; then
    echo "Pulling latest changes from origin/main..."
    git pull --rebase origin main

    echo "Pushing to origin main branch..."
    git branch -M main
    git push -u origin main
else
    echo "No remote 'origin' found. Please set the remote URL first."
    exit 1
fi

# Handle version tag safely
if git rev-parse "$VERSION" >/dev/null 2>&1; then
    if git tag --points-at HEAD | grep -q "$VERSION"; then
        echo "Tag '$VERSION' already exists on this commit. Skipping re-tagging."
    else
        echo "Warning: Tag '$VERSION' already exists but points to a different commit."
        echo "Skipping tagging to avoid overwriting an existing version tag."
    fi
else
    echo "Tagging current commit with version $VERSION"
    git tag -a "$VERSION" -m "Release version $VERSION"
    git push origin "$VERSION"
fi

echo "Done."
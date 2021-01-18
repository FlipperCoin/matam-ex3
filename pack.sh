#!/usr/bin/env bash

rm -f Submission.zip
zip -j Submission.zip dry/dry.cpp
zip Submission.zip partA/date_wrap.* partA/exceptions.*
zip Submission.zip partB/base_event.* partB/closed_event.* partB/custom_event.* partB/event_container.* partB/festival.* partB/one_time_event.* partB/open_event.* partB/recurring_event.* partB/shared_pointer.* partB/vector.*
zip Submission.zip partC/schedule.*
#pragma once

#include "pitchvis.hh"
#include "notes.hh"
#include "operation.hh"
#include <QLabel>
#include <QList>

class NoteLabel;
typedef QList<NoteLabel*> NoteLabels;

class NoteGraphWidget: public QLabel
{
	Q_OBJECT

public:

	NoteGraphWidget(QWidget *parent = 0);

	void clear();
	void setLyrics(QString lyrics);
	void setLyrics(const VocalTrack &track);
	void updateNotes();

	void selectNote(NoteLabel* note);
	NoteLabel* selectedNote() const { return m_selectedNote; }

	int getNoteLabelId(NoteLabel* note) const;
	NoteLabels& noteLabels() { return m_notes; }
	void doOperation(const Operation& op, Operation::OperationFlags flags = Operation::NORMAL);

	int s2px(double sec) const;
	double px2s(int px) const;
	int n2px(int note) const;
	int px2n(int px) const;
	int h() const { return m_pitch.height; }


signals:
	void updateNoteInfo(NoteLabel*);
	void operationDone(const Operation&);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void mouseDoubleClickEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);
	void keyPressEvent(QKeyEvent *event);

private:
	void finalizeNewLyrics();

	int  m_requiredWidth;
	QPoint m_panHotSpot;
	NoteLabel* m_selectedNote;
	enum NoteAction { NONE, RESIZE, MOVE } m_selectedAction;
	bool m_actionHappened;
	NoteLabels m_notes;
	PitchVis m_pitch;
};


struct FloatingGap
{
	FloatingGap(int x): begin(x), end(x), m_notesWidth() {}

	void addNote(NoteLabel* n);
	bool isEmpty() const { return notes.empty(); }
	int width() const { return end - begin; }
	int minWidth() const;
	int notesWidth() const { return m_notesWidth; }

	int begin;
	int end;

	NoteLabels notes;

private:
	int m_notesWidth;
};
